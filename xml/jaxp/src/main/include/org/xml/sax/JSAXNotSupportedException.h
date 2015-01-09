#ifndef ORG_XML_SAX_SAXNOT_SUPPORTED_EXCEPTION_H
#define ORG_XML_SAX_SAXNOT_SUPPORTED_EXCEPTION_H

#include "org/xml/sax/JSAXException.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.SAXNotSupportedException", simpleName="SAXNotSupportedException");
            class JCPP_EXPORT JSAXNotSupportedException : public JSAXException{
            private:
            	static const jlong serialVersionUID = -1422818934641823846LL;

            protected:
                JSAXNotSupportedException(jcpp::lang::JClass* _class);
                friend class JSAXNotSupportedExceptionClass;

            public:
                JSAXNotSupportedException();

                JSAXNotSupportedException(JString* message);

                static jcpp::lang::JClass* getClazz();

                virtual ~JSAXNotSupportedException();
            };
        }
    }
}
#endif
