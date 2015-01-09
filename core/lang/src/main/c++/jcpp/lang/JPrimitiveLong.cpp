#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveLongClass : public jcpp::lang::JClass{
          public:
            JPrimitiveLongClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("long");
                this->name=new JString("long");
                this->simpleName=new JString("long");
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

        jcpp::lang::JClass* JPrimitiveLong::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveLongClass();
            }
            return clazz;
        }

        JPrimitiveLong::JPrimitiveLong(jlong value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveLong::JPrimitiveLong():JObject(getClazz()){
            this->value=0;
        }

        jint JPrimitiveLong::compareTo(JObject* o){
            JPrimitiveLong* s=dynamic_cast<JPrimitiveLong*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveLong::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveLong* s=dynamic_cast<JPrimitiveLong*>(other);
            return value==s->value;
        }

        void JPrimitiveLong::set(jlong value){
            this->value=value;
        }

        jlong JPrimitiveLong::get(){
            return value;
        }

        jint JPrimitiveLong::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveLong::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveLong::~JPrimitiveLong(){
        }
    }
}
