#include "jcpp/util/JTimerTask.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        jint JTimerTask::VIRGIN = 0;

        jint JTimerTask::SCHEDULED = 1;

        jint JTimerTask::EXECUTED = 2;

        jint JTimerTask::CANCELLED = 3;

        JTimerTask::JTimerTask(JClass* _class):JObject(_class){
            this->lockObject=new JObject();
            state=VIRGIN;
            nextExecutionTime=0;
            period=0;
        }

        jbool JTimerTask::cancel(){
            synchronized(lockObject, {
                jbool result = (state == SCHEDULED);
                state = CANCELLED;
                return result;
            })
        }

        jlong JTimerTask::scheduledExecutionTime() {
            synchronized(lockObject,{
                return (period < 0 ? nextExecutionTime + period : nextExecutionTime - period);
            })
        }

        JTimerTask::~JTimerTask(){
        }
    }
}
