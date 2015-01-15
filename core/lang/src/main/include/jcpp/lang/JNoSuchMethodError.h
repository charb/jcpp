#ifndef JCPP_LANG_NOSUCH_METHOD_ERROR_H
#define JCPP_LANG_NOSUCH_METHOD_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NoSuchMethodError", simpleName="NoSuchMethodError");
        class JCPP_EXPORT JNoSuchMethodError : public JIncompatibleClassChangeError {
        private:
        	static const jlong serialVersionUID = -3765521442372831335LL;

        protected:
            JNoSuchMethodError(jcpp::lang::JClass* _class);

        public:
            JNoSuchMethodError();

            JNoSuchMethodError(JString* message);

            JNoSuchMethodError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JNoSuchMethodError();
        };
    }
}

#endif
