#ifndef JCPP_LANG_JNOCLASS_DEF_FOUND_ERROR_H
#define JCPP_LANG_JNOCLASS_DEF_FOUND_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NoClassDefFoundError", simpleName="NoClassDefFoundError");
        class JCPP_EXPORT JNoClassDefFoundError : public JLinkageError {
        private:
        	static const jlong serialVersionUID = 9095859863287012458LL;

        protected:
            JNoClassDefFoundError(jcpp::lang::JClass* _class);

        public:
            JNoClassDefFoundError();

            JNoClassDefFoundError(JString* message);

            JNoClassDefFoundError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JNoClassDefFoundError();
        };
    }
}

#endif
