#ifndef JCPP_LANG_INSTANTIATION_ERROR_H
#define JCPP_LANG_INSTANTIATION_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.InstantiationError", simpleName="InstantiationError");
        class JCPP_EXPORT JInstantiationError : public JIncompatibleClassChangeError {
        private:
        	static const jlong serialVersionUID = -4885810657349421204LL;

        protected:
            JInstantiationError(jcpp::lang::JClass* _class);

        public:
            JInstantiationError();

            JInstantiationError(JString* message);

            JInstantiationError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JInstantiationError();
        };
    }
}

#endif
