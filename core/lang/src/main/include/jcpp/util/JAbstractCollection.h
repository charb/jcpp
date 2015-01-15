#ifndef JCPP_UTIL_JABSTRACTCOLLECTION_H
#define JCPP_UTIL_JABSTRACTCOLLECTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;

namespace jcpp{
	namespace lang{
		class JClass;
	}

    namespace util{

    	// @Class(canonicalName="java.util.AbstractCollection", simpleName="AbstractCollection");
        class JCPP_EXPORT JAbstractCollection: public JObject, public virtual JCollection{
        protected:
            JAbstractCollection(jcpp::lang::JClass* _class);

        public:
            static jcpp::lang::JClass* getClazz();

            virtual jbool isEmpty();

            virtual jbool contains(JObject* o);

            virtual JPrimitiveObjectArray* toArray();

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

            virtual jbool add(JObject* e);

            virtual jbool remove(JObject* o);

            virtual jbool containsAll(JCollection* c);

            virtual jbool addAll(JCollection* c);

            virtual jbool removeAll(JCollection* c);

            virtual jbool retainAll(JCollection* c);

            virtual void clear();

            virtual JString* toString();

            virtual ~JAbstractCollection();
        };
    }
}

#endif
