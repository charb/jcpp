#ifndef JCPP_XML_INTERNAL_PARSER_PARSER2_H
#define JCPP_XML_INTERNAL_PARSER_PARSER2_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/util/JHashtable.h"
#include "jcpp/util/JVector.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "org/xml/sax/helpers/JNamespaceSupport.h"
#include "org/xml/sax/ext/JDeclHandler.h"
#include "org/xml/sax/ext/JLexicalHandler.h"
#include "jcpp/xml/internal/parser/JContentModel.h"
#include "jcpp/xml/internal/parser/JAttributesExImpl.h"
#include "jcpp/xml/internal/parser/JExternalEntity.h"
#include "jcpp/xml/internal/parser/JElementDecl.h"
#include "jcpp/xml/internal/parser/JAttributeDecl.h"
#include "jcpp/xml/internal/parser/JElementValidator.h"
#include "jcpp/xml/internal/parser/JInputEntity.h"

using namespace jcpp::util;
using namespace org::xml::sax;
using namespace org::xml::sax::helpers;
using namespace org::xml::sax::ext;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{    

            	// @Class(canonicalName="javax.xml.internal.parser.Parser2", simpleName="Parser2");
            	class JCPP_EXPORT JParser2 : public JObject{
                protected:

            		// @Class(canonicalName="javax.xml.internal.parser.Parser2$DocLocator", simpleName="Parser2$DocLocator");
                    class JDocLocator : public JObject, public JLocator {
                    protected:
                        JParser2* parser2;
                    public:
                        JDocLocator(JParser2* parser2);

                        static JClass* getClazz();

                        virtual JString* getPublicId();

                        virtual JString* getSystemId();

                        virtual jint getLineNumber();

                        virtual jint getColumnNumber();

                        virtual ~JDocLocator();
                    };

                    // @Class(canonicalName="javax.xml.internal.parser.Parser2$NameCacheEntry", simpleName="Parser2$NameCacheEntry");
                    class JNameCacheEntry : public JObject {
                    public:
                        JString* name;
                        JPrimitiveCharArray* chars;
                        JNameCacheEntry* next;

                        JNameCacheEntry();

                        static JClass* getClazz();

                        virtual jbool matches(JPrimitiveCharArray* value, jint len);

                        virtual ~JNameCacheEntry();
                    };

                    // @Class(canonicalName="javax.xml.internal.parser.Parser2$NameCache", simpleName="Parser2$NameCache");
                    class JNameCache : public JObject{
                        protected:
                            JPrimitiveObjectArray*  hashtable;
                        
                        public:
                            JNameCache();

                            static JClass* getClazz();

                            virtual JString* lookup(JPrimitiveCharArray* value, jint len);

                            virtual JParser2::JNameCacheEntry* lookupEntry(JPrimitiveCharArray* value, jint len);

                            virtual ~JNameCache();
                    };
    
                    // @Class(canonicalName="javax.xml.internal.parser.Parser2$NullHandler", simpleName="Parser2$NullHandler");
                    class JNullHandler : public JDefaultHandler, public JLexicalHandler, public JDeclHandler{
                    public:
                        JNullHandler();

                        static JClass* getClazz();

                        virtual void startDTD(JString* name, JString* publicId, JString* systemId);

                        virtual void endDTD();

                        virtual void startEntity(JString* name);

                        virtual void endEntity(JString* name);

                        virtual void startCDATA();

                        virtual void endCDATA();

                        virtual void comment(JPrimitiveCharArray* ch, jint start, jint length);

                        virtual void elementDecl(JString* name, JString* model);

                        virtual void attributeDecl(JString* eName, JString* aName, JString* type,JString* valueDefault, JString* value);
        
                        virtual void internalEntityDecl(JString* name, JString* value);

                        virtual void externalEntityDecl(JString* name, JString* publicId,JString* systemId);

                        virtual ~JNullHandler();
                    };

                    JInputEntity* in;
                    JAttributesExImpl* attTmp;
                    JStringBuffer* strTmp;
                    JPrimitiveCharArray* nameTmp;
                    JNameCache* nameCache;
                    JPrimitiveCharArray* charTmp;
                    JPrimitiveObjectArray* namePartsTmp;
                    jbool seenNSDecl;
                    JNamespaceSupport* nsSupport;
                    JVector* nsAttTmp;
                    jbool isValidating;
                    jbool fastStandalone;
                    jbool isInAttribute;
                    jbool namespaces;
                    jbool prefixes;
                    jbool inExternalPE;
                    jbool doLexicalPE;
                    jbool donePrologue;
                    jbool isStandalone;
                    JString* rootElementName;
                    jbool ignoreDeclarations;
                    JHashtable* elements;
                    JHashtable* params;
                    JHashtable* notations;
                    JHashtable* entities;
                    JContentHandler* contentHandler;
                    JDTDHandler* dtdHandler;
                    JEntityResolver* resolver;
                    JErrorHandler* errHandler;
                    JLocator* locator;
                    JDeclHandler* declHandler;
                    JLexicalHandler* lexicalHandler;
                    JParser2(JClass* _class);

                    static jbool supportValidation;
                    static JString*         strANY ;
                    static JString*         strEMPTY;
                    static JParser2::JNullHandler* nullHandler;
                    static JString* XmlLang;

                public:
                    JParser2();                    

                    static JClass* getClazz();

                    virtual void setNamespaceFeatures(jbool namespaces, jbool prefixes);

                    virtual void setEntityResolver(JEntityResolver* resolver);

                    virtual void setDTDHandler(JDTDHandler* handler);

                    virtual void setContentHandler(JContentHandler* handler);

                    virtual void setErrorHandler(JErrorHandler* handler);

                    virtual void setLexicalHandler(JLexicalHandler* handler);

                    virtual void setDeclHandler(JDeclHandler* handler);

                    virtual void parse(JInputSource* in);

                    virtual void setFastStandalone(jbool value);

                    virtual jbool isFastStandalone();

                    virtual void pushInputBuffer(JPrimitiveCharArray* buf, jint offset, jint len);

                    virtual void setIsValidating(jbool value);

                    virtual void init ();

                    virtual void setHandlers();

                    virtual void builtin(JString* entityName, JString* entityValue);

                    virtual void parseInternal(JInputSource* input);

                    virtual void afterRoot();

                    virtual void afterDocument();

                    virtual void whitespace(JString* roleId);

                    virtual jbool maybeWhitespace();

                    virtual JString* maybeGetName();

                    virtual JNameCacheEntry* maybeGetNameCacheEntry();

                    virtual JString* getNmtoken();

                    virtual JNameCacheEntry* nameCharString(jchar c);

                    virtual void parseLiteral(jbool isEntityValue);

                    virtual void expandEntityInLiteral(JString* name,JHashtable* table,jbool isEntityValue);

                    virtual JString* getQuotedString(JString* type, JString* extra);

                    virtual JString* parsePublicId();

                    virtual jbool maybeComment(jbool skipStart);

                    virtual jbool maybePI(jbool skipStart);

                    virtual void maybeXmlDecl();

                    virtual JString* maybeReadAttribute(JString* name, jbool must);

                    virtual void readVersion(jbool must, JString* versionNum);

                    virtual void maybeMisc(jbool eofOK);

                    virtual JString* getMarkupDeclname(JString* roleId, jbool qname);

                    virtual jbool maybeDoctypeDecl();

                    virtual jbool maybeMarkupDecl();

                    virtual void readStandalone();

                    virtual jbool isXmlLang(JString* value);

                    virtual jbool maybeElement(JElementValidator* validator);

                    virtual JVector* processAttributeNS(JString* attQName, JString* type,JString* value, JString* defaultValue,jbool isSpecified, jbool isDefaulting,JVector* exceptions);

                    virtual JPrimitiveObjectArray* processName(JString* qName, jbool isAttribute,jbool useException);

                    virtual JElementValidator* newValidator(JElementDecl* element);

                    virtual void validateAttributeSyntax(JAttributeDecl* attr, JString* value);

                    virtual jbool defaultAttributes(JElementDecl* element);

                    virtual void content(JElementDecl* element,jbool allowEOF,JElementValidator* validator);

                    virtual jbool maybeElementDecl();

                    virtual JString* getMixedOrChildren(JElementDecl* element);

                    virtual JContentModel* newContentModel(JString* tag);

                    virtual JContentModel* newContentModel(jchar type, JContentModel* next);

                    virtual JContentModel* getcps(JString* element,JInputEntity* start);

                    virtual JContentModel* getFrequency(JContentModel* original);

                    virtual void getMixed(JString* element, JInputEntity* start);

                    virtual jbool maybeAttlistDecl();

                    virtual JString* normalize(jbool invalidIfNeeded);

                    virtual jbool maybeConditionalSect();

                    virtual jbool maybeReferenceInContent(JElementDecl* element,JElementValidator* validator);

                    virtual jint parseCharNumber();

                    virtual jint surrogatesToCharTmp(jint ucs4);

                    virtual void expandEntityInContent(JElementDecl* element,JString* name,JElementValidator* validator);

                    virtual jbool maybePEReference();

                    virtual jbool maybeEntityDecl();

                    virtual JExternalEntity* maybeExternalID();

                    virtual JString* parseSystemId();

                    virtual JString* resolveURI(JString* uri);

                    virtual void maybeTextDecl();

                    virtual jbool externalParsedEntity(JElementDecl* element,JExternalEntity* next,JElementValidator* validator);

                    virtual void externalParameterEntity(JExternalEntity* next);

                    virtual void readEncoding(jbool must);

                    virtual jbool maybeNotationDecl();

                    virtual jchar getc();

                    virtual void ungetc();

                    virtual jbool peek(JString* s);

                    virtual JInputEntity* peekDeclaration(JString* s);

                    virtual void nextChar(jchar c, JString* location, JString* near);

                    virtual void pushReader(JPrimitiveCharArray* buf, JString* name, jbool isGeneral);

                    virtual jbool pushReader(JExternalEntity* next);

                    virtual void warning(JString* messageId);

                    virtual void error(JString* messageId);

                    virtual void error(JString* messageId, JException* e);

                    virtual void fatal(JString* message);

                    virtual void fatal(JString* messageId, JException* e);

                    virtual ~JParser2();
                };
            }
        }
    }
}

#endif
