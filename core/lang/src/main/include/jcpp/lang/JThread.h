#ifndef JCPP_LANG_JTHREAD_H
#define JCPP_LANG_JTHREAD_H

#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using jcpp::native::api::nthread::NativeThread;

/**
 *  TODO check:
 *  - ThreadGroup
 *  - interrupt
 *  - Thread State
 *  - UncaughtExceptionHandler
 *  - Stack Trace
 */
namespace jcpp{
	namespace lang{

		// @Class(canonicalName="java.lang.Thread", simpleName="Thread");
        class JCPP_EXPORT JThread : public JObject, public JRunnable {

        public:
			// @Class(canonicalName="java.lang.Thread$State", simpleName="Thread$State");
			class JCPP_EXPORT JState : public JEnum {
			    protected:

        		JState(JString* name, JPrimitiveInt* ordinal);

			    public:

			        static JClass* getClazz();

			        static JState* NEW;

			        static JState* RUNNABLE;

			        static JState* TERMINATED;

			        virtual ~JState();
			    };

        private:
        	static JThread* mainJThread;

        	// @IgnoreReflection()
			NativeThread* nativeThread;

			JRunnable* target;
            JClassLoader* contextClassLoader;
            jbool bDaemon;

            // @IgnoreReflection()
			JThread(const JThread&);
			// @IgnoreReflection()
			JThread& operator =(const JThread&);
			// @IgnoreReflection()
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

            JState* getState();

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
