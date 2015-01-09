#ifndef JCPP_LANG_JILLEGAL_MONITOR_STATEEXCEPTION_H
#define JCPP_LANG_JILLEGAL_MONITOR_STATEEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIllegalMonitorStateException : public JRuntimeException{
        protected:
            JIllegalMonitorStateException(jcpp::lang::JClass* _class);

        public:
            JIllegalMonitorStateException();

            JIllegalMonitorStateException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIllegalMonitorStateException();
        };
    }
}

#endif
