#ifndef JCPP_LANG_JUNSATISFIED_LINK_ERROR_H
#define JCPP_LANG_JUNSATISFIED_LINK_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.UnsatisfiedLinkError", simpleName="UnsatisfiedLinkError");
        class JCPP_EXPORT JUnsatisfiedLinkError : public JLinkageError {
        private:
        	static const jlong serialVersionUID = -4019343241616879428LL;

        protected:
            JUnsatisfiedLinkError(jcpp::lang::JClass* _class);

        public:
            JUnsatisfiedLinkError();

            JUnsatisfiedLinkError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JUnsatisfiedLinkError();
        };
    }
}

#endif
