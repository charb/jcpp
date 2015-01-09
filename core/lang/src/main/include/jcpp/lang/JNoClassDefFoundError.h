#ifndef JCPP_LANG_JNOCLASS_DEF_FOUND_ERROR_H
#define JCPP_LANG_JNOCLASS_DEF_FOUND_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNoClassDefFoundError : public JLinkageError {
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
