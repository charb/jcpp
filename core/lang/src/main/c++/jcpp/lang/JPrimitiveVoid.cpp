#include "jcpp/lang/JPrimitiveVoid.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveVoidClass : public jcpp::lang::JClass{
          public:
            JPrimitiveVoidClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("void");
                this->name=new JString("void");
                this->simpleName=new JString("void");
                this->bIsPrimitive=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JPrimitiveVoid::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveVoidClass();
            }
            return clazz;
        }

        JPrimitiveVoid::~JPrimitiveVoid(){
        }
    }
}
