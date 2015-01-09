#ifndef JCPP_LANG_JUNSATISFIED_LINK_ERROR_H
#define JCPP_LANG_JUNSATISFIED_LINK_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JUnsatisfiedLinkError : public JLinkageError {
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
