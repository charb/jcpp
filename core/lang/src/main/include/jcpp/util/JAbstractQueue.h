#ifndef JCPP_UTIL_JABSTRACTQUEUE_H
#define JCPP_UTIL_JABSTRACTQUEUE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JAbstractCollection.h"
#include "jcpp/util/JQueue.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JAbstractQueue : public JAbstractCollection, public JQueue{
        protected:
            JAbstractQueue(JClass* _class);

        public:
            static JClass* getClazz();

            virtual jbool add(JObject* e);

            virtual JObject* remove();

            virtual JObject* element();

            virtual void clear();

            virtual jbool addAll(JCollection* c);

            virtual ~JAbstractQueue();
        };
    }
}

#endif
