#ifndef JCPP_LANG_JVERIFYERROR_H
#define JCPP_LANG_JVERIFYERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.VerifyError", simpleName="VerifyError");
        class JCPP_EXPORT JVerifyError : public JLinkageError {
        private:
        	static const jlong serialVersionUID = 7001962396098498785LL;

        protected:
            JVerifyError(jcpp::lang::JClass* _class);

        public:
            JVerifyError();

            JVerifyError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JVerifyError();
        };
    }
}

#endif
