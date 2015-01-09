#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveShortClass : public jcpp::lang::JClass{
          public:
            JPrimitiveShortClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("short");
                this->name=new JString("short");
                this->simpleName=new JString("short");
                this->bIsPrimitive=true;
            }

            virtual void initialize(){
                addInterface(JComparable::getClazz());
                addInterface(JSerializable::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JPrimitiveShort::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveShortClass();
            }
            return clazz;
        }

        JPrimitiveShort::JPrimitiveShort(jshort value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveShort::JPrimitiveShort():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveShort::compareTo(JObject* o){
            JPrimitiveShort* s=dynamic_cast<JPrimitiveShort*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveShort::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveShort* s=dynamic_cast<JPrimitiveShort*>(other);
            return value==s->value;
        }

        void JPrimitiveShort::set(jshort value){
            this->value=value;
        }

        jshort JPrimitiveShort::get(){
            return value;
        }

        jint JPrimitiveShort::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveShort::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveShort::~JPrimitiveShort(){
        }
    }
}
