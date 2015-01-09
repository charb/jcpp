#ifndef ORG_XML_SAX_SAXPARSE_EXCEPTION_H
#define ORG_XML_SAX_SAXPARSE_EXCEPTION_H

#include "org/xml/sax/JSAXException.h"

using namespace jcpp::lang;

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.SAXParseException", simpleName="SAXParseException");
            class JCPP_EXPORT JSAXParseException : public JSAXException{
            private:
            	static const jlong serialVersionUID = -5651165872476709336LL;

            protected:
                JString* publicId;
                JString* systemId;
                JPrimitiveInt* lineNumber;
                JPrimitiveInt* columnNumber;

                JSAXParseException(jcpp::lang::JClass* _class);
                friend class JSAXParseExceptionClass;

            public:
                JSAXParseException();

                JSAXParseException(JString* message);

                JSAXParseException(JString* message, JException* cause);

                JSAXParseException(JString* message, JString* publicId, JString* systemId,jint lineNumber, jint columnNumber);

                JSAXParseException(JString* message, JString* publicId, JString* systemId,jint lineNumber, jint columnNumber, JException* e);

                static jcpp::lang::JClass* getClazz();

                virtual JString* getPublicId();

                virtual JString* getSystemId();

                virtual jint getLineNumber();

                virtual jint getColumnNumber();

                virtual JString* toString();

                virtual ~JSAXParseException();
            };
        }
    }
}
#endif
