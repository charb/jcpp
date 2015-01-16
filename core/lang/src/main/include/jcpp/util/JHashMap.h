#ifndef JCPP_UTIL_JHASHMAP_H
#define JCPP_UTIL_JHASHMAP_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JAbstractMap.h"
#include "jcpp/util/JSet.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JNode;
        class JTreeNode;
        class JHashIterator;
        class JEntryIterator;
        class JHashMapKeySetImpl;
        class JHashMapValues;
        class JHashMapEntrySetImpl;
        class JHashMapClass;
        class JHashSet;

        // @Class(canonicalName="java.util.HashMap", simpleName="HashMap");
        class JCPP_EXPORT JHashMap : public JAbstractMap, public JCloneable, public JSerializable{
        private:
        	static const jlong serialVersionUID = 362498820763181265LL;

        protected:
            JPrimitiveObjectArray* table;
            jint isize;
            jint modCount;
            JPrimitiveInt* threshold;
            JPrimitiveFloat* loadFactor;

            static jint tableSizeFor(jint cap);
            static jint hash(JObject* key);
            static jcpp::lang::JClass* comparableClassFor(JObject* x);
            static jint compareComparables(jcpp::lang::JClass* kc, JObject* k, JObject* x);

            virtual JNode* newNode(jint hash, JObject* key, JObject* value, JNode* next);
            virtual JNode* replacementNode(JNode* p, JNode* next);
            virtual JTreeNode* newTreeNode(jint hash, JObject* key, JObject* value, JNode* next);
            virtual JTreeNode* replacementTreeNode(JNode* p, JNode* next);
            virtual void reinitialize();
            virtual void afterNodeAccess(JNode* p);
            virtual void afterNodeInsertion(jbool evict);
            virtual void afterNodeRemoval(JNode* p);
            virtual void putMapEntries(JMap* m, jbool evict);
            virtual JObject* putVal(jint hash, JObject* key, JObject* value, jbool onlyIfAbsent,jbool evict);
            virtual JNode* getNode(jint hash, JObject* key);
            virtual JPrimitiveObjectArray* resize();
            virtual void treeifyBin(JPrimitiveObjectArray* tab, jint hash);
            virtual JNode* removeNode(jint hash, JObject* key, JObject* value,jbool matchValue, jbool movable);
            virtual jint capacity();
            virtual JIterator* newKeyIterator();
            virtual JIterator* newValueIterator();
            virtual JIterator* newEntryIterator();
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            
            friend class JNode;
            friend class JTreeNode;
            friend class JHashIterator;
            friend class JEntryIterator;
            friend class JHashMapKeySetImpl;
            friend class JHashMapValues;
            friend class JHashMapEntrySetImpl;
            friend class JHashMapClass;
            friend class JHashSet;

        public:
            JHashMap(jint initialCapacity, jfloat loadFactor);

            JHashMap(JMap* c);

            JHashMap();

            static jcpp::lang::JClass* getClazz();

            virtual jint size();

            virtual jbool isEmpty();

            virtual JObject* get(JObject* key);

            virtual jbool containsKey(JObject* key);

            virtual JObject* put(JObject* key, JObject* value);

            virtual void putAll(JMap* m);

            virtual JObject* remove(JObject* key);

            virtual void clear();

            virtual jbool containsValue(JObject* value);

            virtual JHashMap* clone();

            virtual JSet* keySet();

            virtual JCollection* values();

            virtual JSet* entrySet();

            virtual ~JHashMap();
        };
    }
}
#endif
