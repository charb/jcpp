#ifndef JCPP_LANG_JINCOMPATIBLE_CLASS_CHANGE_ERROR
#define JCPP_LANG_JINCOMPATIBLE_CLASS_CHANGE_ERROR

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.IncompatibleClassChangeError", simpleName="IncompatibleClassChangeError");
        class JCPP_EXPORT JIncompatibleClassChangeError : public JLinkageError {
        private:
        	static const jlong serialVersionUID = -4914975503642802119LL;

        protected:
            JIncompatibleClassChangeError(jcpp::lang::JClass* _class);

        public:
            JIncompatibleClassChangeError();

            JIncompatibleClassChangeError(JString* message);

            JIncompatibleClassChangeError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JIncompatibleClassChangeError();
        };
    }
}

#endif
