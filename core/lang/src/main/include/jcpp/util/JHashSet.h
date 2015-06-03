#ifndef JCPP_UTIL_JHASHSET_H
#define JCPP_UTIL_JHASHSET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/util/JRandomAccess.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.HashSet", simpleName="HashSet");
        class JCPP_EXPORT JHashSet : public JAbstractSet, public JCloneable, public JSerializable{
        private:
        	static const jlong serialVersionUID = -5024744406713321676LL;
            static JObject* PRESENT;
        protected:
            JHashMap* map;
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);
            friend class JHashSetClass;

        public:
            JHashSet();

            JHashSet(jint initialCapacity, jfloat loadFactor);

            JHashSet(JCollection* c);

            static JClass* getClazz();

            virtual JIterator* iterator();

            virtual jint size();

            virtual JPrimitiveObjectArray* toArray();

            virtual jbool containsAll(JCollection* c);

            virtual jbool addAll(JCollection* c);

            virtual jbool removeAll(JCollection* c);

            virtual jbool retainAll(JCollection* c);

            virtual jbool equals(JObject* c);

            virtual jint hashCode();

            virtual jbool isEmpty();

            virtual jbool contains(JObject* o);

            virtual jbool add(JObject* item);

            virtual jbool remove(JObject* e);

            virtual void clear();

            virtual JHashSet* clone();

            virtual ~JHashSet();
        };
    }
}
#endif
