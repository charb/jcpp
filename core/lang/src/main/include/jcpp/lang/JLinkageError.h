#ifndef JCPP_LANG_JLINKAGEERROR_H
#define JCPP_LANG_JLINKAGEERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.LinkageError", simpleName="LinkageError");
        class JCPP_EXPORT JLinkageError : public JError {
        private:
        	static const jlong serialVersionUID = 3579600108157160122LL;

        protected:
            JLinkageError(jcpp::lang::JClass* _class);

        public:
            JLinkageError();

            JLinkageError(JString* message);

            JLinkageError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JLinkageError();
        };
    }
}

#endif
