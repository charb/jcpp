#ifndef JCPP_UTIL_CONCURRENT_JBLOCKING_QUEUE_H
#define JCPP_UTIL_CONCURRENT_JBLOCKING_QUEUE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/JQueue.h"
#include "jcpp/util/JCollection.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.BlockingQueue", simpleName="BlockingQueue");
            class JCPP_EXPORT JBlockingQueue : public JQueue{
            public:
                static JClass* getClazz();

                virtual jbool add(JObject* e)=0;

                virtual jbool offer(JObject* e)=0;

                virtual void put(JObject* e)=0;

                virtual jbool offer(JObject* e,jlong l)=0;

                virtual JObject* take()=0;

                virtual JObject* poll(jlong l)=0;

                virtual jint remainingCapacity()=0;

                virtual jbool remove(JObject* e)=0;

                virtual jbool contains(JObject* e)=0;

                virtual jint drainTo(JCollection* c)=0;

                virtual jint drainTo(JCollection* c,jint max)=0;

                virtual ~JBlockingQueue();
            };
        }
    }
}

#endif
