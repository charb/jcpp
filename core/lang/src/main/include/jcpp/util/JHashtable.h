#ifndef JCPP_UTIL_JHASHTABLE_H
#define JCPP_UTIL_JHASHTABLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JDictionary.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JHashtable : public JDictionary, public JMap, public JCloneable, public JSerializable{
        protected:
            JPrimitiveObjectArray* table;
            jint count;
            JPrimitiveInt* threshold;
            JPrimitiveFloat* loadFactor;
            jint modCount;
            JHashtable(JClass* _class);
            void init(jint initialCapacity, jfloat loadFactor);
            void rehash();
            void addEntry(jint hash, JObject* key, JObject* value, jint index);
            JEnumeration* getEnumeration(jint type);
            JIterator* getIterator(jint type);
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            void reconstitutionPut(JPrimitiveObjectArray* tab, JObject* key, JObject* value);
            friend class JHashtableKeySetImpl;
            friend class JHashtableClass;
            friend class JHashtableEnumeratorImpl;
            friend class JHashtableValues;
            friend class JHashtableEntrySetImpl;

        public:
            JHashtable(jint initialCapacity, jfloat loadFactor);

            JHashtable(jint initialCapacity);

            JHashtable();

            JHashtable(JMap* c);

            static JClass* getClazz();

            virtual jint size();

            virtual jbool isEmpty();

            virtual JEnumeration* keys();

            virtual JEnumeration* elements();

            virtual jbool contains(JObject* value);

            virtual jbool containsValue(JObject* value);

            virtual jbool containsKey(JObject* key);

            virtual JObject* get(JObject* key);

            virtual JObject* put(JObject* key, JObject* value);

            virtual JObject* remove(JObject* key);

            virtual void putAll(JMap* m);

            virtual void clear();

            virtual JHashtable* clone();

            virtual JString* toString();

            virtual JSet* keySet();

            virtual JSet* entrySet();

            virtual JCollection* values();

            virtual jbool equals(JObject* o);

            virtual jint hashCode();

            virtual ~JHashtable();
        };
    }
}

#endif
