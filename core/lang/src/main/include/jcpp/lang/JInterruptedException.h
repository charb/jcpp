#ifndef JCPP_LANG_JINTERRUPTED_EXCEPTION_H
#define JCPP_LANG_JINTERRUPTED_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JInterruptedException : public JException{
        public:
            JInterruptedException();

            JInterruptedException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JInterruptedException();
        };
    }
}

#endif
