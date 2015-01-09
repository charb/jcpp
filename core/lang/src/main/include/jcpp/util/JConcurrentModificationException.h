#ifndef JCPP_UTIL_JCONCURRENTMODIFICATIONEXCEPTION_H
#define JCPP_UTIL_JCONCURRENTMODIFICATIONEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JConcurrentModificationException : public JRuntimeException{
        protected:
            JConcurrentModificationException(jcpp::lang::JClass* _class);

        public:
            JConcurrentModificationException();

            JConcurrentModificationException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JConcurrentModificationException();
        };
    }
}
#endif
