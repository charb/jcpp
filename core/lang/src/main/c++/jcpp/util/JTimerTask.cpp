#include "jcpp/util/JTimerTask.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        class JTimerTaskClass : public JClass{
        public:
            JTimerTaskClass():JClass(){
                this->canonicalName=new JString("java.util.TimerTask");
                this->name=new JString("java.util.TimerTask");
                this->simpleName=new JString("TimerTask");
            }

            virtual void initialize(){
                addInterface(JRunnable::getClazz());
            }

            virtual JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JTimerTask::getClazz(){
            if (clazz==null){
                clazz=new JTimerTaskClass();
            }
            return clazz;
        }

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
