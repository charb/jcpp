#ifndef JCPP_LANG_JPRIMITIVEARRAY_H
#define JCPP_LANG_JPRIMITIVEARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @IgnoreReflection()
    	// @IgnorePackageReflection()
        class JCPP_EXPORT JPrimitiveArray : public JObject{
        protected:
            jcpp::lang::JClass* componentType;
            jint len;
            void checkType(JObject* o);
            void setSize(jint len);

        public:
            JPrimitiveArray(jcpp::lang::JClass* arrayClass, jint len);

            JPrimitiveArray(JPrimitiveArray* a);
            
            static jcpp::lang::JClass* getClazz(jcpp::lang::JClass* componentType);
            
            virtual jcpp::lang::JClass* getComponentType();

            virtual jint size();
            
            virtual JObject* get(jint i) = 0;
                        
            virtual void set(jint i,JObject* value) = 0;
            
            virtual jbool equals(JObject* other);
            
            virtual ~JPrimitiveArray();
        };
    }
}

#endif
