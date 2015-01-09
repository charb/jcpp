#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveVoid.h"

namespace jcpp{
    namespace lang{
        class JVoidClass : public jcpp::lang::JClass{
          public:
            JVoidClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Void");
                this->name=new JString("java.lang.Void");
                this->simpleName=new JString("Void");
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JVoid::getClazz(){
            if (clazz==null){
                clazz=new JVoidClass();
            }
            return clazz;
        }

        jcpp::lang::JClass* JVoid::TYPE = JPrimitiveVoid::getClazz();

        JVoid::~JVoid(){
        }
    }
}

