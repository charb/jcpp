#ifndef JCPP_XML_INTERNAL_PARSER_VALIDATING_PARSER_H
#define JCPP_XML_INTERNAL_PARSER_VALIDATING_PARSER_H

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
#include "jcpp/xml/internal/parser/JParser2.h"
#include "jcpp/xml/internal/parser/JContentModelState.h"

using namespace jcpp::util;
using namespace org::xml::sax;
using namespace org::xml::sax::helpers;
using namespace org::xml::sax::ext;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{    

            	// @Class(canonicalName="javax.xml.internal.parser.ValidatingParser", simpleName="ValidatingParser");
                class JCPP_EXPORT JValidatingParser : public JParser2{
                protected:

                	// @Class(canonicalName="javax.xml.internal.parser.ValidatingParser$EmptyValidator", simpleName="ValidatingParser$EmptyValidator");
                    class JEmptyValidator : public JElementValidator{
                    protected:
                        JValidatingParser* parser;

                    public:
                        JEmptyValidator(JValidatingParser* parser);

                        static JClass* getClazz();

                        virtual void consume(JString* token);

                        virtual void text ();

                        virtual ~JEmptyValidator();
                    };

                    // @Class(canonicalName="javax.xml.internal.parser.ValidatingParser$MixedValidator", simpleName="ValidatingParser$MixedValidator");
                    class JMixedValidator : public JElementValidator{
                    protected:  
                        JElementDecl* element;
                        JValidatingParser* parser;

                    public:
                        JMixedValidator(JValidatingParser* parser,JElementDecl* element);

                        static JClass* getClazz();
                        
                        virtual void consume(JString* type);

                        virtual ~JMixedValidator();
                    };

                    // @Class(canonicalName="javax.xml.internal.parser.ValidatingParser$ChildrenValidator", simpleName="ValidatingParser$ChildrenValidator");
                    class JChildrenValidator : public JElementValidator{
                    protected:
                        JValidatingParser* parser;
                        JContentModelState* state;
                        JString* name;

                    public:
                        JChildrenValidator(JValidatingParser* parser,JElementDecl* element);

                        static JClass* getClazz();

                        virtual void consume(JString* token);

                        virtual void text();

                        virtual void done();

                        virtual ~JChildrenValidator();
                    };

                    JEmptyValidator* EMPTY;
                    JHashtable* ids;

                public:
                    JValidatingParser();

                    JValidatingParser(jbool rejectValidityErrors);

                    static JClass* getClazz();

                    virtual void afterRoot();

                    virtual void afterDocument();

                    virtual void validateAttributeSyntax(JAttributeDecl* attr, JString* value);

                    virtual JContentModel* newContentModel(JString* tag);

                    virtual JContentModel* newContentModel(jchar type, JContentModel* next);

                    virtual JElementValidator* newValidator(JElementDecl* element);

                    virtual jbool isUnparsedEntity(JString* name);

                    virtual ~JValidatingParser();
                };
            }
        }
    }
}

#endif
