#ifndef JCPP_LANG_JCLASSCASTEXCEPTION_H
#define JCPP_LANG_JCLASSCASTEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JClassCastException : public JRuntimeException{
        public:
            JClassCastException();

            JClassCastException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JClassCastException();
        };
    }
}

#endif
