#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveIntClass : public jcpp::lang::JClass{
          public:
            JPrimitiveIntClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("int");
                this->name=new JString("int");
                this->simpleName=new JString("int");
                this->bIsPrimitive=true;
            }

            virtual void initialize(){
                addInterface(JComparable::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JPrimitiveInt::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveIntClass();
            }
            return clazz;
        }

        JPrimitiveInt::JPrimitiveInt(jint value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveInt::JPrimitiveInt():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveInt::compareTo(JObject* o){
            JPrimitiveInt* s=dynamic_cast<JPrimitiveInt*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveInt::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveInt* s=dynamic_cast<JPrimitiveInt*>(other);
            return value==s->value;
        }

        void JPrimitiveInt::set(jint value){
            this->value=value;
        }

        jint JPrimitiveInt::get(){
            return value;
        }

        JPrimitiveInt* JPrimitiveInt::clone(){
            return new JPrimitiveInt(value);
        }

        jint JPrimitiveInt::hashCode(){
            return value;
        }

        JString* JPrimitiveInt::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveInt::~JPrimitiveInt(){
        }
    }
}
