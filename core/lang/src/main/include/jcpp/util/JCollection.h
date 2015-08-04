#ifndef JCPP_UTIL_JCOLLECTION_H
#define JCPP_UTIL_JCOLLECTION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JIterable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Collection", simpleName="Collection");
        class JCPP_EXPORT JCollection : public JIterable{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jint size()=0;

            virtual jbool isEmpty()=0;

            virtual jbool contains(JObject*)=0;

            virtual JIterator* iterator()=0;
            
            virtual JPrimitiveObjectArray* toArray()=0;

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a)=0;
            
            virtual jbool add(JObject* e)=0;
            
            virtual jbool remove(JObject* o)=0;
            
            virtual jbool containsAll(JCollection* c)=0;
            
            virtual jbool addAll(JCollection* c)=0;
            
            virtual jbool removeAll(JCollection* c)=0;
            
            virtual jbool retainAll(JCollection* c)=0;
            
            virtual void clear()=0;
            



            virtual ~JCollection();
        };
    }
}

#endif
