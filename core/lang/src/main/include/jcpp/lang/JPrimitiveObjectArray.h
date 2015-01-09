#ifndef JCPP_LANG_JPRIMITIVEOBJECTARRAY_H
#define JCPP_LANG_JPRIMITIVEOBJECTARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"


namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveObjectArray : public JPrimitiveArray{
        protected:
            JObject** objects;
        public:
            JPrimitiveObjectArray(jcpp::lang::JClass* arrayClass, jint len);

            JPrimitiveObjectArray(JPrimitiveObjectArray* a);
            
            static jcpp::lang::JClass* getClazz(jcpp::lang::JClass* componentType);

            static jcpp::lang::JClass* getClazz();

            virtual JObject* get(jint i);
                        
            virtual void set(jint i,JObject* value);
            
            virtual JPrimitiveObjectArray* clone();

            virtual void finalize();

            virtual jbool equals(JObject* o);

            virtual ~JPrimitiveObjectArray();
        };
    }
}

#endif
