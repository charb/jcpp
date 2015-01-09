#ifndef JCPP_IO_INPUT_HANDLETABLE_H
#define JCPP_IO_INPUT_HANDLETABLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputHandleList.h"
#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectInputStream$HandleTable", simpleName="ObjectInputStream$HandleTable");
        class JInputHandleTable : public JObject{
            static const jbyte STATUS_OK = 1;
            static const jbyte STATUS_UNKNOWN = 2;
            static const jbyte STATUS_EXCEPTION = 3;

            JPrimitiveByteArray* status;
            JPrimitiveObjectArray* entries;
            JPrimitiveObjectArray* deps;
            jint lowDep;
            jint size;
            void grow();

        public:
            JInputHandleTable(jint initialCapacity);

            static jcpp::lang::JClass* getClazz();

            virtual jint assign(JObject* obj);

            virtual void markDependency(jint dependent, jint target);

            virtual void markException(jint handle, JClassNotFoundException* ex);

            virtual void finish(jint handle);
            
            virtual void setObject(jint handle, JObject* obj);
            
            virtual JObject* lookupObject(jint handle);
            
            virtual JClassNotFoundException* lookupException(jint handle);
            
            virtual void clear();
            
            virtual jint getSize();
            
            ~JInputHandleTable();
         };
    }
}

#endif
