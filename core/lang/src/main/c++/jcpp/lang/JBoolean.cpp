#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JBoolean* JBoolean::TRUE = new JBoolean(true);

        JBoolean* JBoolean::FALSE = new JBoolean(false);

        jcpp::lang::JClass* JBoolean::TYPE = JPrimitiveBoolean::getClazz();

        JString* JBoolean::TRUE_STRING = new JString("true");

        JString* JBoolean::FALSE_STRING = new JString("false");        

        jbool JBoolean::parseBoolean(JString* s){
            return s->equals(TRUE_STRING);
        }

        JBoolean* JBoolean::valueOf(jbool b){
            return (b ? TRUE : FALSE);
        }

        JBoolean* JBoolean::valueOf(JString* s){
            return (parseBoolean(s) ? TRUE : FALSE );
        }

        JString* JBoolean::toString(jbool b){
            return (b ? TRUE_STRING : FALSE_STRING);
        }

        jint JBoolean::hashCode(jbool value){
            return (value ? 1231 : 1237);
        }

        jint JBoolean::compare(jbool v1,jbool v2){
            return (v1 == v2) ? 0 : (v1 ? 1 : -1);
        }

        jbool JBoolean::getBoolean(JString* name){
            jbool result = parseBoolean(JSystem::getProperty(name));
            return result;
        }

        JBoolean::JBoolean(jbool value):JObject(getClazz()){
            this->value=new JPrimitiveBoolean(value);
        }

        JBoolean::JBoolean():JObject(getClazz()){
            this->value=new JPrimitiveBoolean(false);
        }

        jbool JBoolean::equals(JObject* other){
            if ((other == null) || other->getClass()!=getClazz()){
                return false;
            }
            JBoolean* b=dynamic_cast<JBoolean*>(other);
            return value->equals(b->value);
        }

        void JBoolean::set(jbool value){
            this->value->set(value);
        }

        jbool JBoolean::get(){
            return value->get();
        }

        jbool JBoolean::booleanValue(){
            return value->get();
        }

        JPrimitiveBoolean* JBoolean::getPrimitiveBoolean(){
            return value;
        }

        void JBoolean::setPrimitiveBoolean(JPrimitiveBoolean* value){
            this->value=value;
        }

        jint JBoolean::compareTo(JObject *o){
            JBoolean* b=dynamic_cast<JBoolean*>(o);
            return compare(value->get(),b->value->get());
        }

        jint JBoolean::hashCode(){
            return hashCode(value->get());
        }

        JString* JBoolean::toString(){
            return (value!=null && value->get() ? TRUE_STRING : FALSE_STRING);
        }

        JBoolean::~JBoolean(){
        }
    }
}
