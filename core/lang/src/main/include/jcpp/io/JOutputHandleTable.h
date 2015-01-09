#ifndef JCPP_IO_OUTPUTHANDLETABLE_H
#define JCPP_IO_OUTPUTHANDLETABLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JMap.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectOutputStream$HandleTable", simpleName="ObjectOutputStream$HandleTable");
        class JOutputHandleTable : public JObject{
        private:
            jint isize;
            jint threshold;
            jfloat loadFactor;
            JPrimitiveIntArray* spine;
            JPrimitiveIntArray* next;
            JPrimitiveObjectArray* objs;
            void insert(JObject* obj, jint handle);
            void growSpine();
            void growEntries();
            jint hash(JObject* obj);

        public:
            JOutputHandleTable(jint initialCapacity,jfloat loadFactor);
            
            static jcpp::lang::JClass* getClazz();

            virtual jint assign(JObject *obj);
            
            virtual jint lookup(JObject* obj);

            virtual void clear();
            
            virtual jint size();
            
            ~JOutputHandleTable();
        };
    }
}

#endif
