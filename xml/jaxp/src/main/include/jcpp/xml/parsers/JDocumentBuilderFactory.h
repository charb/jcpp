#ifndef JCPP_XML_PARSERS_DOCUMENT_BUILDER_FACTORY_H
#define JCPP_XML_PARSERS_DOCUMENT_BUILDER_FACTORY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JFile.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JDOMImplementation.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JErrorHandler.h"
#include "jcpp/xml/parsers/JDocumentBuilder.h"

using namespace jcpp::io;
using namespace org::w3c::dom;
using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace parsers{            

        	// @Class(canonicalName="javax.xml.parsers.DocumentBuilderFactory", simpleName="DocumentBuilderFactory");
        	class JCPP_EXPORT JDocumentBuilderFactory : public JObject{
            protected:
                jbool validating;
                jbool namespaceAware;
                jbool whitespace;
                jbool expandEntityRef;
                jbool ignoreComments;
                jbool coalescing;
                JDocumentBuilderFactory(JClass* _class);

            public:
                static JClass* getClazz();

                static JDocumentBuilderFactory* newInstance();

                static JDocumentBuilderFactory* newInstance(JString* factoryClassName, JClassLoader* classLoader);

                virtual JDocumentBuilder* newDocumentBuilder()=0;
          
                virtual void setNamespaceAware(jbool awareness);

                virtual void setValidating(jbool validating);

                virtual void setIgnoringElementContentWhitespace(jbool whitespace);

                virtual void setExpandEntityReferences(jbool expandEntityRef);

                virtual void setIgnoringComments(jbool ignoreComments);

                virtual void setCoalescing(jbool coalescing);

                virtual jbool isNamespaceAware();

                virtual jbool isValidating();

                virtual jbool isIgnoringElementContentWhitespace();

                virtual jbool isExpandEntityReferences();

                virtual jbool isIgnoringComments();

                virtual jbool isCoalescing();

                virtual void setAttribute(JString* name, JObject* value)=0;

                virtual JObject* getAttribute(JString* name)=0;

                virtual void setFeature(JString* name, jbool value)=0;

                virtual jbool getFeature(JString* name)=0;

                virtual void setXIncludeAware(jbool state);

                virtual jbool isXIncludeAware();

                virtual ~JDocumentBuilderFactory();
            };
        }
    }
}

#endif
