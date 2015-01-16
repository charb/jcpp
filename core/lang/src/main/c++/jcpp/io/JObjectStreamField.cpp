#include "jcpp/io/JObjectStreamField.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JObjectStreamField::JObjectStreamField():JObject(getClazz()){
            this->name=null;
            this->signature=null;
            this->type=null;
            this->unshared=false;
            this->field=null;
            offset=0;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JString* name,jcpp::lang::JClass* type):JObject(getClazz()){
            this->name=name;
            this->type=type;
            this->unshared=false;
            this->signature=type->getSignature();
            this->field=null;
            offset=0;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JString* name,jcpp::lang::JClass* type,jbool unshared):JObject(getClazz()){
            this->name=name;
            this->type=type;
            this->unshared=unshared;
            this->signature=type->getSignature();
            this->field=null;
            offset=0;
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JString* name,JString* signature,jbool unshared):JObject(getClazz()){
            this->name=name;
            this->signature=signature;
            this->unshared=unshared;
            this->field=null;
            offset=0;
            switch(signature->charAt(0)){
                case 'Z':
                    type = JPrimitiveBoolean::getClazz();
                    break;
                case 'B':
                    type = JPrimitiveByte::getClazz();
                    break;
                case 'C':
                    type = JPrimitiveChar::getClazz();
                    break;
                case 'S':
                    type = JPrimitiveShort::getClazz();
                    break;
                case 'I':
                    type = JPrimitiveInt::getClazz();
                    break;
                case 'J':
                    type = JPrimitiveLong::getClazz();
                    break;
                case 'F':
                    type = JPrimitiveFloat::getClazz();
                    break;
                case 'D':
                    type = JPrimitiveDouble::getClazz();
                    break;
                case 'L':
                case '[':
                    type = JObject::getClazz();
                    break;
                default:
                    throw new JIllegalArgumentException(new JString("illegal signature"));
            }
            setTypeString();
        }

        JObjectStreamField::JObjectStreamField(JField* field,jbool unshared,jbool showType):JObject(getClazz()){
            this->field=field;
            this->unshared=unshared;
            this->name=field->getName();
            jcpp::lang::JClass* ftype=field->getType();
            type=(showType||ftype->isPrimitive()?ftype:JObject::getClazz());
            signature=ftype->getSignature();
            offset=0;
            setTypeString();
        }

        JString* JObjectStreamField::getName(){
            return name;
        }

        jcpp::lang::JClass* JObjectStreamField::getType(){
            return type;
        }

        jchar JObjectStreamField::getTypeCode(){
            return (jchar)signature->charAt(0);
        }

        void JObjectStreamField::setTypeString(){
            if (isPrimitive()){
                typeString=null;
            }else{
                typeString=signature;
            }
        }

        JString* JObjectStreamField::getTypeString(){
            return typeString;
        }

        jint JObjectStreamField::getOffset(){
            return offset;
        }

        void JObjectStreamField::setOffset(jint offset){
            this->offset=offset;
        }

        jbool JObjectStreamField::isPrimitive(){
            jchar tcode=(jchar)signature->charAt(0);
            return (tcode!='L') && (tcode!='[');
        }

        jbool JObjectStreamField::isUnshared(){
            return unshared;
        }

        JField* JObjectStreamField::getField(){
            return field;
        }

        JField* JObjectStreamField::getField(JObject* obj){
            if (field!=null){
                return field;
            }
            JClass* defCl = obj->getClass();
            while (defCl != null) {
                if (defCl->hasDeclaredField(name)){
                    field = defCl->getDeclaredField(name);
                    return field;
                }else {
                    defCl = defCl->getSuperclass();
                }
            }
            return field;
        }

        void JObjectStreamField::setField(JField* f){
            field=f;
        }

        JString* JObjectStreamField::getSignature(){
            return signature;
        }

        jint JObjectStreamField::compareTo(JObject* o){
            JObjectStreamField* other=dynamic_cast<JObjectStreamField*>(o);
            jbool isPrim = getType()->isPrimitive();
            if (isPrim != other->getType()->isPrimitive()) {
                return isPrim ? -1 : 1;
            }
            return getName()->compareTo(other->getName());
        }

        JString* JObjectStreamField::toString() {
            JStringBuilder* builder=new JStringBuilder();
            builder->append(signature)->append(' ')->append(name);
            return builder->toString();
        }

        JObjectStreamField::~JObjectStreamField(){
        }
    }
}
