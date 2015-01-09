#include "jcpp/xml/internal/parser/JValidatingParser.h"
#include "jcpp/xml/internal/parser/JInternalEntity.h"
#include "jcpp/xml/internal/parser/JExternalEntity.h"
#include "jcpp/xml/internal/parser/JResolver.h"
#include "jcpp/xml/internal/util/JXmlChars.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/util/JStringTokenizer.h"
#include "org/xml/sax/JSAXException.h"
#include "org/xml/sax/JSAXParseException.h"
#include "org/xml/sax/JHandlerBase.h"

using namespace jcpp::xml::internal::util;
using namespace jcpp::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JValidatingParser::JValidatingParser():JParser2(getClazz()){
                    ids=new JHashtable();
                    EMPTY=new JValidatingParser::JEmptyValidator(this);
                    setIsValidating (true);
                }

                // @Class(canonicalName="javax.xml.internal.parser.ValidatingParser$1", simpleName="ValidatingParser$1");
                class JHandlerBaseImpl : public JHandlerBase{
                public:
                    JHandlerBaseImpl():JHandlerBase(getClazz()){
                    }

                    static JClass* getClazz();

                    virtual void error(JSAXParseException* x){ 
                        throw x; 
                    }

                    ~JHandlerBaseImpl(){
                    }
                };

                JValidatingParser::JValidatingParser(jbool rejectValidityErrors):JParser2(getClazz()){
                    ids=new JHashtable();
                    EMPTY=new JValidatingParser::JEmptyValidator(this);
                    if (rejectValidityErrors){
                        setErrorHandler(new JHandlerBaseImpl());
                    }
                }

                JValidatingParser::JEmptyValidator::JEmptyValidator(JValidatingParser* parser):JElementValidator(getClazz()){
                    this->parser=parser;
                }

                void JValidatingParser::JEmptyValidator::consume(JString* token){
                    parser->error(new JString("Error"));
                }

                void JValidatingParser::JEmptyValidator::text(){
                    parser->error(new JString("Error"));
                }

                JValidatingParser::JEmptyValidator::~JEmptyValidator(){
                }

                JValidatingParser::JMixedValidator::JMixedValidator(JValidatingParser* parser,JElementDecl* element):JElementValidator(getClazz()){
                    this->parser=parser;
                    this->element=element;
                }
                
                void JValidatingParser::JMixedValidator::consume(JString* type){
                    JString* model = element->contentType;

                    for (jint index = 8; (index = model->indexOf(type, index + 1)) >= 9;) {
                        jchar c=0;
                        if (model->charAt (index -1) != '|'){
                            continue;
                        }
                        c = model->charAt(index + type->length());
                        if (c == '|' || c == ')'){
                            return;
                        }
                    }
                    parser->error(new JString("Error"));
                }

                JValidatingParser::JMixedValidator::~JMixedValidator(){
                }

                JValidatingParser::JChildrenValidator::JChildrenValidator(JValidatingParser* parser,JElementDecl* element):JElementValidator(getClazz()){
                    this->parser=parser;
                    state = new JContentModelState (element->model);
                    name = element->name;
                }

                void JValidatingParser::JChildrenValidator::consume(JString* token){
                    if (state == null){
                        parser->error(new JString("Error"));
                    }else{
                        state = state->advance(token);
                    }
                }

                void JValidatingParser::JChildrenValidator::text(){
                    parser->error(new JString("Error"));
                }

                void JValidatingParser::JChildrenValidator::done(){
                    if (state != null && !state->terminate()){
                        parser->error(new JString("Error"));
                    }
                }

                JValidatingParser::JChildrenValidator::~JChildrenValidator(){
                }

                void JValidatingParser::afterRoot(){
                    for (JEnumeration* e = ids->keys ();e->hasMoreElements ();) {
                        JString* id = dynamic_cast<JString*>(e->nextElement());
                        JBoolean* value = dynamic_cast<JBoolean*>(ids->get(id));
                        if (JBoolean::FALSE == value){
                            error(new JString("Error"));
                        }
                    }
                }

                void JValidatingParser::afterDocument(){
                    ids->clear();
                }

                void JValidatingParser::validateAttributeSyntax(JAttributeDecl* attr, JString* value){
                    if (JAttributeDecl::ID == attr->type) {
                        if (!JXmlNames::isName(value)){
                            error(new JString("Error"));
                        }

                        JBoolean* b = dynamic_cast<JBoolean*>(ids->get(value));
                        if (b == null || b->equals(JBoolean::FALSE)){
                            ids->put(value, JBoolean::TRUE);
                        }else{
                            error(new JString("Error"));
                        }

                    } else if (JAttributeDecl::IDREF == attr->type) {
                        if (!JXmlNames::isName (value)){
                            error(new JString("Error"));
                        }

                        JBoolean* b = dynamic_cast<JBoolean*>(ids->get(value));
                        if (b == null){
                            ids->put(value, JBoolean::FALSE);
                        }

                    } else if (JAttributeDecl::IDREFS == attr->type) {
                        JStringTokenizer* tokenizer = new JStringTokenizer(value);
                        JBoolean* b=null;
                        jbool sawValue = false;

                        while (tokenizer->hasMoreTokens()) {
                            value = tokenizer->nextToken();
                            if (!JXmlNames::isName(value)){
                                error(new JString("Error"));
                            }
                            b = dynamic_cast<JBoolean*>(ids->get(value));
                            if (b == null){
                                ids->put(value,JBoolean::FALSE);
                            }
                            sawValue = true;
                        }
                        if (!sawValue){
                            error(new JString("Error"));
                        }

                    } else if (JAttributeDecl::NMTOKEN == attr->type) {
                        if (!JXmlNames::isNmtoken(value)){
                            error(new JString("Error"));
                        }

                    } else if (JAttributeDecl::NMTOKENS == attr->type) {
                        JStringTokenizer* tokenizer = new JStringTokenizer(value);
                        jbool sawValue=false;

                        while (tokenizer->hasMoreTokens()) {
                            value = tokenizer->nextToken();
                            if (!JXmlNames::isNmtoken(value)){
                                error(new JString("Error"));
                            }
                            sawValue = true;
                        }
                        if (!sawValue){
                            error(new JString("Error"));
                        }

                    } else if (JAttributeDecl::ENUMERATION == attr->type) {
                        for (jint i = 0; i < attr->values->size(); i++){
                            if (value->equals(attr->values->get(i))){
                                return;
                            }
                        }
                        error(new JString("Error"));

                    } else if (JAttributeDecl::NOTATION == attr->type) {
                        for (jint i = 0; i < attr->values->size(); i++){
                            if (value->equals(attr->values->get(i))){
                                return;
                            }
                        }
                        error(new JString("Error"));

                    } else if (JAttributeDecl::ENTITY == attr->type) {
                        if (!isUnparsedEntity (value)){
                            error(new JString("Error"));
                        }

                    } else if (JAttributeDecl::ENTITIES == attr->type) {
                        JStringTokenizer* tokenizer = new JStringTokenizer (value);
                        jbool sawValue = false;

                        while (tokenizer->hasMoreTokens()) {
                            value = tokenizer->nextToken();
                            if (!isUnparsedEntity(value)){
                                error(new JString("Error"));
                            }
                            sawValue = true;
                        }
                        if (!sawValue){
                            error(new JString("Error"));
                        }

                    } else if (JAttributeDecl::CDATA != attr->type){
                        throw new JInternalError(attr->type);
                    }
                }

                JContentModel* JValidatingParser::newContentModel(JString* tag){
                    return new JContentModel(tag);
                }

                JContentModel* JValidatingParser::newContentModel(jchar type, JContentModel* next){
                    return new JContentModel(type, next);
                }

                JElementValidator* JValidatingParser::newValidator(JElementDecl* element){
                    if (element->validator != null){
                        return element->validator;
                    }
                    if (element->model != null){
                        return new JChildrenValidator(this,element);
                    }

                    if (element->contentType == null || strANY == element->contentType){
                        element->validator = JElementValidator::ANY;
                    
                    }else if (strEMPTY == element->contentType){
                        element->validator = EMPTY;
                    
                    }else{
                        element->validator = new JValidatingParser::JMixedValidator(this,element);
                    }
                    return element->validator;
                }

                jbool JValidatingParser::isUnparsedEntity(JString* name){
                    JObject* e = entities->get(name);
                    if (e == null || !(e->isInstanceOf(JExternalEntity::getClazz()))){
                        return false;
                    }
                    return (dynamic_cast<JExternalEntity*>(e))->notation != null;
                }

                JValidatingParser::~JValidatingParser(){
                }
            }
        }
    }
}
