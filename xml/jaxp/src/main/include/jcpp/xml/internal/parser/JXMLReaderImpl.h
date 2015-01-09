#ifndef JCPP_XML_INTERNAL_PARSER_XML_READER_IMPL_H
#define JCPP_XML_INTERNAL_PARSER_XML_READER_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JHashtable.h"
#include "jcpp/io/JInputStream.h"
#include "org/xml/sax/JXMLReader.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/ext/JLexicalHandler.h"
#include "org/xml/sax/ext/JDeclHandler.h"
#include "org/xml/sax/JContentHandler.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JEntityResolver.h"
#include "jcpp/xml/internal/parser/JParser2.h"

using namespace org::xml::sax;
using namespace org::xml::sax::ext;
using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.XMLReaderImpl", simpleName="XMLReaderImpl");
            	class JCPP_EXPORT JXMLReaderImpl : public JObject, public JXMLReader{
                protected:
                    static JString* FEATURES;
                    static JString* NAMESPACES;
                    static JString* NAMESPACE_PREFIXES;
                    static JString* STRING_INTERNING ;
                    static JString* VALIDATION;
                    static JString* EXTERNAL_GENERAL;
                    static JString* EXTERNAL_PARAMETER;
                    static JString* LEXICAL_PARAMETER_ENTITIES;
                    static JString* PROPERTIES;
                    static JString* LEXICAL_HANDLER;
                    static JString* DECLARATION_HANDLER;

                    jbool namespaces;
                    jbool prefixes;
                    jbool validation;
                    JLexicalHandler* lexicalHandler;
                    JDeclHandler* declHandler;
                    JContentHandler* contentHandler;
                    JDTDHandler* dtdHandler;
                    JErrorHandler* errorHandler;
                    JEntityResolver* entityResolver;
                    JParser2* parser;
                    jbool parsing;  

                public:
                    JXMLReaderImpl();

                    static JClass* getClazz();

                    virtual jbool getFeature(JString* name);

                    virtual void setFeature(JString* name, jbool state);

                    virtual JObject* getProperty(JString* name);

                    virtual void setProperty(JString* name, JObject* value);

                    virtual void setEntityResolver(JEntityResolver* resolver);

                    virtual JEntityResolver* getEntityResolver();

                    virtual void setDTDHandler(JDTDHandler* handler);

                    virtual JDTDHandler* getDTDHandler();

                    virtual void setContentHandler(JContentHandler* handler);

                    virtual JContentHandler* getContentHandler();

                    virtual void setErrorHandler(JErrorHandler* handler);

                    virtual JErrorHandler* getErrorHandler();

                    virtual void parse(JString* systemId);

                    virtual void parse(JInputSource* input);

                    virtual void checkNotParsing(JString* type, JString* name);

                    virtual ~JXMLReaderImpl();
                };
            }
        }
    }
}

#endif
