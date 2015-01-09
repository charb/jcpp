#ifndef JCPP_UTIL_JTIMER_H
#define JCPP_UTIL_JTIMER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/JTimerTask.h"
#include "jcpp/lang/JThread.h"

using namespace jcpp::lang;

//TODO test
namespace jcpp{
    namespace util{
        class JTimerTask;
        class JCPP_EXPORT JTimer : public JObject{
        protected:
            class JCPP_EXPORT JTaskQueue : public JObject{
            protected:
                JPrimitiveObjectArray* queue;
                jint isize;
                friend JTimer;

            public:
                JTaskQueue();
                static JClass* getClazz();
                virtual jint size();
                virtual void add(JTimerTask* task);
                virtual JTimerTask* getMin();
                virtual JTimerTask* get(jint i);
                virtual void removeMin();
                virtual void quickRemove(jint i);
                virtual void rescheduleMin(jlong newTime);
                virtual jbool isEmpty();
                virtual void clear();
                virtual void fixUp(jint k);
                virtual void fixDown(jint k);
                virtual void heapify();
                virtual ~JTaskQueue();

            };

            class JCPP_EXPORT JTimerThread : public JThread{
            protected:
                jbool newTasksMayBeScheduled;
                JTaskQueue* queue;
                void mainLoop();
                friend JTimer;

            public:
                JTimerThread(JTaskQueue* queue);
                static JClass* getClazz();
                virtual void run();
                virtual ~JTimerThread();
            };

            static jint nextSerialNumber;
            static jint serialNumer();

            JTaskQueue* queue;
            JTimerThread* thread;
            JTimer(JClass* _class);
            void sched(JTimerTask* task, jlong time, jlong period);

            friend class JTimerTask;
            friend class JTimerClass;

        public:
            JTimer();
            JTimer(jbool isDaemon);
            JTimer(JString* name);
            JTimer(JString* name,jbool isDaemon);
            static JClass* getClazz();
            virtual void schedule(JTimerTask* task, jlong delay);
            virtual void schedule(JTimerTask* task, jlong delay, jlong period);
            virtual void scheduleAtFixedRate(JTimerTask* task, jlong delay, jlong period);
            virtual void cancel();
            virtual jint purge();            
            virtual ~JTimer();
        };
    }
}

#endif
