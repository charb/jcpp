#ifndef JCPP_UTIL_JQUEUE_H
#define JCPP_UTIL_JQUEUE_H 

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/io/JExternalizable.h"
#include "jcpp/util/JIterator.h"

using namespace std;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JQueue : public virtual JCollection{
        public:
            static JClass* getClazz();

            virtual jbool add(JObject* e)=0;

            virtual jbool offer(JObject* e)=0;

            virtual JObject* remove()=0;

            virtual JObject* poll()=0;

            virtual JObject* element()=0;

            virtual JObject* peek()=0;

            virtual ~JQueue();
        };
    }
}


#endif
