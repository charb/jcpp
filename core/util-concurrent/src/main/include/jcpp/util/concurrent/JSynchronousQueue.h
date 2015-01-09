#ifndef JCPP_UTIL_CONCURRENT_JSYNCHRONOUS_QUEUE_H
#define JCPP_UTIL_CONCURRENT_JSYNCHRONOUS_QUEUE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JQueue.h"
#include "jcpp/util/JAbstractQueue.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/concurrent/JBlockingQueue.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.SynchronousQueue", simpleName="SynchronousQueue");
            class JCPP_EXPORT JSynchronousQueue : public JAbstractQueue, public JBlockingQueue, public JSerializable{
            private:
            	static const jlong serialVersionUID = -3223113410248163686LL;

            protected:
                JArrayList* elements;
                jint waitingToTake;

            public:
                JSynchronousQueue();

                static JClass* getClazz();

                virtual jbool add(JObject* e);

                virtual JObject* remove();

                virtual JObject* element();

                virtual void put(JObject* e);

                virtual jbool offer(JObject* e,jlong l);

                virtual jbool offer(JObject* e);

                virtual JObject* take();

                virtual JObject* poll(jlong l);

                virtual JObject* poll();
                
                virtual jbool isEmpty();

                virtual jint size();

                virtual jint remainingCapacity();

                virtual void clear();

                virtual jbool contains(JObject* o);
 
                virtual jbool remove(JObject* o);

                virtual jbool containsAll(JCollection* c);

                virtual jbool removeAll(JCollection* c);

                virtual jbool retainAll(JCollection* c);

                virtual JObject* peek();

                virtual JIterator* iterator();

                virtual JPrimitiveObjectArray* toArray();

                virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

                virtual jint drainTo(JCollection* c);
                
                virtual jint drainTo(JCollection* c,jint max);

                virtual ~JSynchronousQueue();
            };
        }
    }
}

#endif
