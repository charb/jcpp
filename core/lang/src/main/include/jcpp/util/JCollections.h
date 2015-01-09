#ifndef JCPP_UTIL_JCOLLECTIONS_H
#define JCPP_UTIL_JCOLLECTIONS_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JIterable.h"
#include "jcpp/util/JIterator.h"
#include "jcpp/util/JEnumeration.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JComparator.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JCollections : public JObject{
        public:
            static jcpp::lang::JClass* getClazz();

            static void reverse(JList* list);

            static void sort(JList* list,JComparator* c);

            static JCollection* unmodifiableCollection(JCollection* c);

            static JCollection* synchronizedCollection(JCollection* c);

            static JCollection* synchronizedCollection(JCollection* c, JObject* mutex);

            static JList* unmodifiableList(JList* list);

            static JList* synchronizedList(JList* list);

            static JList* synchronizedList(JList* list,JObject* mutex);

            static JSet* synchronizedSet(JSet* s);

            static JSet* synchronizedSet(JSet* s, JObject* mutex);

            static JIterator* emptyIterator();

            static JEnumeration* emptyEnumeration();

            static void swap(JList* list, jint i, jint j);
            
            virtual ~JCollections();
        };
    }
}

#endif
