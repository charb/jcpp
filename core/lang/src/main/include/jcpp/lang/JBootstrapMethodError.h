#ifndef JCPP_LANG_BOOTSTRAP_METHOD_ERROR_H
#define JCPP_LANG_BOOTSTRAP_METHOD_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.BootstrapMethodError", simpleName="BootstrapMethodError");
        class JCPP_EXPORT JBootstrapMethodError : public JLinkageError {
        private:
        	static const jlong serialVersionUID = 292LL;

        protected:
            JBootstrapMethodError(jcpp::lang::JClass* _class);

        public:
            JBootstrapMethodError();

            JBootstrapMethodError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JBootstrapMethodError();
        };
    }
}

#endif
