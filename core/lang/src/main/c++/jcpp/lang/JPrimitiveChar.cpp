#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        class JPrimitiveCharClass : public jcpp::lang::JClass{
          public:
            JPrimitiveCharClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("char");
                this->name=new JString("char");
                this->simpleName=new JString("char");
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

        jcpp::lang::JClass* JPrimitiveChar::getClazz(){
            if (clazz==null){
                clazz=new JPrimitiveCharClass();
            }
            return clazz;
        }

        JPrimitiveChar::JPrimitiveChar(char value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveChar::JPrimitiveChar(jchar value):JObject(getClazz()){
            this->value=value;
        }

        JPrimitiveChar::JPrimitiveChar():JObject(getClazz()){
            this->value=0;
        }

        void JPrimitiveChar::set(jchar value){
            this->value=value;
        }

        jchar JPrimitiveChar::get(){
            return value;
        }

        jint JPrimitiveChar::compareTo(JObject* o){
            JPrimitiveChar* s=dynamic_cast<JPrimitiveChar*>(o);
            return get()-s->get();
        }

        jbool JPrimitiveChar::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JPrimitiveChar* s=dynamic_cast<JPrimitiveChar*>(other);
            return value==s->value;
        }

        jint JPrimitiveChar::hashCode(){
            return (jint)value;
        }

        JString* JPrimitiveChar::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(value);
            return builder->toString();
        }

        JPrimitiveChar::~JPrimitiveChar(){
        }
    }
}
