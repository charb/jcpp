#ifndef JCPP_LANG_JARRAY_STORE_EXCEPTION_H
#define JCPP_LANG_JARRAY_STORE_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JArrayStoreException : public JRuntimeException{
        public:

            JArrayStoreException();

            JArrayStoreException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JArrayStoreException();
        };
    }
}

#endif
