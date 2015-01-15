#ifndef JCPP_UTIL_JTIMERTASK_H
#define JCPP_UTIL_JTIMERTASK_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JRunnable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JTimer;

        // @Class(canonicalName="java.util.TimerTask", simpleName="TimerTask");
        class JCPP_EXPORT JTimerTask : public JRunnable, public JObject{
        protected:
            JObject* lockObject;
            jint state;
            static jint VIRGIN;
            static jint SCHEDULED;
            static jint EXECUTED;
            static jint CANCELLED;
            jlong nextExecutionTime;
            jlong period;
            JTimerTask(JClass* _class);
            friend class JTimer;

        public:
            static JClass* getClazz();

            virtual void run()=0;

            virtual jbool cancel();

            virtual jlong scheduledExecutionTime();

            virtual ~JTimerTask();
        };
    }
}

#endif
