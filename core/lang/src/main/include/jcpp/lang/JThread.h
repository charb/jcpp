#ifndef JCPP_LANG_JTHREAD_H
#define JCPP_LANG_JTHREAD_H

#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using jcpp::native::api::nthread::NativeThread;

namespace jcpp{
	namespace lang{

		/**
		 *  TODO check:
		 *  - ThreadGroup
		 *  - interrupt
		 *  - Thread State
		 *  - UncaughtExceptionHandler
		 *  - Stack Trace
		 */
        class JCPP_EXPORT JThread : public JObject, public JRunnable {

        public:
        	enum JState { NEW, RUNNABLE, TERMINATED };

        private:
        	static JThread* mainJThread;

			NativeThread* nativeThread;

			JRunnable* target;
            JClassLoader* contextClassLoader;
            jbool bDaemon;

			JThread(const JThread&);
			JThread& operator =(const JThread&);

			JThread(NativeThread* mainThread);
        protected:
			JThread(jcpp::lang::JClass* _class);

        public:
		    static const jint MIN_PRIORITY = 1;
		    static const jint NORM_PRIORITY = 5;
		    static const jint MAX_PRIORITY = 10;

            static jcpp::lang::JClass* getClazz();

            static JThread* currentThread();

            static JThread* mainThread();

            static void yield();

            static void sleep(jlong millis);

            static JPrimitiveObjectArray* enumerate();

            JThread();

            JThread(JRunnable* target);

            JThread(JString* name);

            JThread(JRunnable* target, JString* name);
            
            JClassLoader* getContextClassLoader();

            void setContextClassLoader(JClassLoader* c);

            JState getState();

            void start();

            jbool isAlive();

            void suspend();

            void resume();

            void setPriority(jint priority);

            jint getPriority();

            void setName(JString* name);

            JString* getName();

            void join(jlong millis);

            void join();

            jlong getId();

            void setDaemon(jbool bDaemon);

            jbool isDaemon();

            virtual void finalize();

            virtual void run();

            virtual JString* toString();

            virtual jbool equals(JObject* other);

            virtual jint hashCode();

            virtual ~JThread();
        };

    }
}

#endif
