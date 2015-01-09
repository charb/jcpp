#ifndef ORG_W3C_DOM_JDOM_EXCEPTION_H
#define ORG_W3C_DOM_JDOM_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JPrimitiveShort.h"

using namespace jcpp::lang;

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMException", simpleName="DOMException");
            class JCPP_EXPORT JDOMException : public JRuntimeException{
        	private:
        		static const jlong serialVersionUID = 6627732366795969916LL;

            protected:
                JDOMException(jcpp::lang::JClass* _class);

            public:
                JPrimitiveShort* code;

                JDOMException(jshort code);

                JDOMException(jshort code,JString* message);

                JDOMException(jshort code,JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                static jshort INDEX_SIZE_ERR;
                static jshort DOMSTRING_SIZE_ERR;
                static jshort HIERARCHY_REQUEST_ERR;
                static jshort WRONG_DOCUMENT_ERR;
                static jshort INVALID_CHARACTER_ERR;
                static jshort NO_DATA_ALLOWED_ERR;
                static jshort NO_MODIFICATION_ALLOWED_ERR;
                static jshort NOT_FOUND_ERR;
                static jshort NOT_SUPPORTED_ERR;
                static jshort INUSE_ATTRIBUTE_ERR;
                static jshort INVALID_STATE_ERR;
                static jshort SYNTAX_ERR;
                static jshort INVALID_MODIFICATION_ERR;
                static jshort NAMESPACE_ERR;
                static jshort INVALID_ACCESS_ERR;
                static jshort VALIDATION_ERR;
                static jshort TYPE_MISMATCH_ERR;

                virtual ~JDOMException();
            };
        }
    }
}
#endif
