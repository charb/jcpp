#ifndef JCPP_UTIL_JDEQUE_H
#define JCPP_UTIL_JDEQUE_H 

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/io/JExternalizable.h"
#include "jcpp/util/JQueue.h"

using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Deque", simpleName="Deque");
        class JCPP_EXPORT JDeque : public virtual JQueue{
        public:
            static JClass* getClazz();

            virtual void addFirst(JObject* e)=0;

            virtual void addLast(JObject* e)=0;

            virtual jbool offerFirst(JObject* e)=0;

            virtual jbool offerLast(JObject* e)=0;

            virtual JObject* removeFirst()=0;

            virtual JObject* removeLast()=0;

            virtual JObject* pollFirst()=0;

            virtual JObject* pollLast()=0;

            virtual JObject* getFirst()=0;

            virtual JObject* getLast()=0;

            virtual JObject* peekFirst()=0;

            virtual JObject* peekLast()=0;

            virtual jbool removeFirstOccurrence(JObject* o)=0;

            virtual jbool removeLastOccurrence(JObject* o)=0;

            virtual jbool add(JObject* e)=0;

            virtual jbool offer(JObject* e)=0;

            virtual JObject* remove()=0;

            virtual JObject* poll()=0;

            virtual JObject* element()=0;

            virtual JObject* peek()=0;

            virtual void push(JObject* e)=0;

            virtual JObject* pop()=0;

            virtual jbool remove(JObject* o)=0;

            virtual jbool contains(JObject* o)=0;

            virtual jint size()=0;

            virtual JIterator* iterator()=0;

            virtual JIterator* descendingIterator()=0;

            virtual ~JDeque();
        };
    }
}


#endif
