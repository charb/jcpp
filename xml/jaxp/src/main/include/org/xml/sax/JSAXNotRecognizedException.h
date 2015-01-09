#ifndef ORG_XML_SAX_SAXNOT_RECOGNIZED_EXCEPTION_H
#define ORG_XML_SAX_SAXNOT_RECOGNIZED_EXCEPTION_H

#include "org/xml/sax/JSAXException.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.SAXNotRecognizedException", simpleName="SAXNotRecognizedException");
            class JCPP_EXPORT JSAXNotRecognizedException : public JSAXException{
            private:
            	static const jlong serialVersionUID = 5440506620509557213LL;

            protected:
                JSAXNotRecognizedException(jcpp::lang::JClass* _class);
                friend class JSAXNotRecognizedExceptionClass;

            public:
                JSAXNotRecognizedException();

                JSAXNotRecognizedException(JString* message);

                static jcpp::lang::JClass* getClazz();

                virtual ~JSAXNotRecognizedException();
            };
        }
    }
}
#endif
