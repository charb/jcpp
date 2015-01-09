#ifndef ORG_XML_SAX_SAXEXCEPTION_H
#define ORG_XML_SAX_SAXEXCEPTION_H

#include "jcpp/lang/JException.h"

using namespace jcpp::lang;

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.SAXException", simpleName="SAXException");
            class JCPP_EXPORT JSAXException : public JException{
            private:
            	static const jlong serialVersionUID = 583241635256073760LL;

            protected:
                JException* exception;
                JSAXException(jcpp::lang::JClass* _class);
                friend class JSAXExceptionClass;

            public:
                JSAXException();

                JSAXException(JString* message);

                JSAXException(JException* cause);

                JSAXException(JString* message, JException* cause);

                static jcpp::lang::JClass* getClazz();

                virtual JString* getMessage();

                virtual JException* getException();

                virtual JThrowable* getCause();

                virtual ~JSAXException();
            };
        }
    }
}
#endif
