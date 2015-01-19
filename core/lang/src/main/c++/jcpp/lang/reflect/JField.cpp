#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            void JField::setPublic(){
            	iModifiers|=JModifier::PUBLIC;
            }

            void JField::setPrivate(){
            	iModifiers|=JModifier::PRIVATE;
            }

            void JField::setProtected(){
            	iModifiers|=JModifier::PROTECTED;
            }

            void JField::setStatic(){
			   iModifiers|=JModifier::STATIC;
		   }

		   void JField::setFinal(){
			   iModifiers|=JModifier::FINAL;
		   }

		   void JField::setTransient() {
			   iModifiers|=JModifier::TRANSIENT;
		   }

            JField::JField(JString* name,jcpp::lang::JClass* type,jcpp::lang::JClass* declaringClass, getter g,setter s,adressReference adr):JAccessibleObject(getClazz()){
                this->name=name;
                this->type=type;
                this->declaringClass=declaringClass;
                this->g=g;
                this->s=s;
                this->adr=adr;
                annotations=new JArrayList();
                this->iModifiers=0;
            }

            JField* JField::addAnnotation(JAnnotation* ann){
                annotations->add(dynamic_cast<JObject*>(ann));
                return this;
            }

            jbool JField::equals(JObject* o){
                if ((o == null) || o->getClass()!=getClazz()){
                    return false;
                }
                JField* f=dynamic_cast<JField*>(o);
                return this->getName()->equals(f->getName()) && 
                       this->getType()==f->getType() &&
                       this->getDeclaringClass()==f->getDeclaringClass();
                return false;
            }

            JObject* JField::get(JObject* object){
                return g(object);
            }

            JAnnotation* JField::getAnnotation(jcpp::lang::JClass* annotationClass){
                for (jint i=0;i<annotations->size();i++){
                    JAnnotation* ann=dynamic_cast<JAnnotation*>(annotations->get(i));
                    if (ann->annotationType()->equals(annotationClass)){
                        return ann;
                    }
                }
                return null;
            }

            jcpp::util::JList* JField::getAnnotations(){
                return annotations;
            }

            jbool JField::getBoolean(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveBoolean::getClazz()){
                    JPrimitiveBoolean* p=dynamic_cast<JPrimitiveBoolean*>(value);
                    return p->get();
                }
                if (value->getClass()==JBoolean::getClazz()){
                    JBoolean* p=dynamic_cast<JBoolean*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a boolean"));
            }

            jbyte JField::getByte(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveByte::getClazz()){
                    JPrimitiveByte* p=dynamic_cast<JPrimitiveByte*>(value);
                    return p->get();
                }
                if (value->getClass()==JByte::getClazz()){
                    JByte* p=dynamic_cast<JByte*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a byte"));
            }

            jchar JField::getChar(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveChar::getClazz()){
                    JPrimitiveChar* p=dynamic_cast<JPrimitiveChar*>(value);
                    return p->get();
                }
                if (value->getClass()==JCharacter::getClazz()){
                    JCharacter* p=dynamic_cast<JCharacter*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a char"));
            }

            jcpp::lang::JClass* JField::getDeclaringClass(){
                return declaringClass;
            }

            jdouble JField::getDouble(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveDouble::getClazz()){
                    JPrimitiveDouble* p=dynamic_cast<JPrimitiveDouble*>(value);
                    return p->get();
                }
                if (value->getClass()==JDouble::getClazz()){
                    JDouble* p=dynamic_cast<JDouble*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a double"));
            }

            jfloat JField::getFloat(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveFloat::getClazz()){
                    JPrimitiveFloat* p=dynamic_cast<JPrimitiveFloat*>(value);
                    return p->get();
                }
                if (value->getClass()==JFloat::getClazz()){
                    JFloat* p=dynamic_cast<JFloat*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a float"));
            }

            jint JField::getInt(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveInt::getClazz()){
                    JPrimitiveInt* p=dynamic_cast<JPrimitiveInt*>(value);
                    return p->get();
                }
                if (value->getClass()==JInteger::getClazz()){
                    JInteger* p=dynamic_cast<JInteger*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a int"));
            }

            jlong JField::getLong(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveLong::getClazz()){
                    JPrimitiveLong* p=dynamic_cast<JPrimitiveLong*>(value);
                    return p->get();
                }
                if (value->getClass()==JLong::getClazz()){
                    JLong* p=dynamic_cast<JLong*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a long"));
            }

            jint JField::getModifiers(){
                return iModifiers;
            }

            JString* JField::getName(){
                return name;
            }

            jshort JField::getShort(JObject* obj){
                JObject* value=get(obj);
                if (value->getClass()==JPrimitiveShort::getClazz()){
                    JPrimitiveShort* p=dynamic_cast<JPrimitiveShort*>(value);
                    return p->get();
                }
                if (value->getClass()==JShort::getClazz()){
                    JShort* p=dynamic_cast<JShort*>(value);
                    return p->get();
                }
                throw new JIllegalArgumentException(new JString("field is not a short"));
            }
                
            jcpp::lang::JClass* JField::getType(){
                return type;
            }
                
            jint JField::hashCode(){
                return getDeclaringClass()->getName()->hashCode()^getName()->hashCode();
            }

            jbool JField::isEnumConstant(){
                return (getModifiers() & JModifier::ENUM) != 0;
            }
                
            void JField::set(JObject* object, JObject* value){
                s(object,value);
            }
                
            void JField::setBoolean(JObject* obj, jbool z){
                set(obj,new JPrimitiveBoolean(z));
            }

            void JField::setByte(JObject* obj, jbyte b){
                set(obj,new JPrimitiveByte(b));
            }

            void JField::setChar(JObject* obj, jchar c){
                set(obj,new JPrimitiveChar(c));
            }

            void JField::setDouble(JObject* obj, jdouble d){
                set(obj,new JPrimitiveDouble(d));
            }

            void JField::setFloat(JObject* obj, jfloat f){
                set(obj,new JPrimitiveFloat(f));
            }

            void JField::setInt(JObject* obj, jint i){
                set(obj,new JPrimitiveInt(i));
            }

            void JField::setLong(JObject* obj, jlong l){
                set(obj,new JPrimitiveLong(l));
            }

            void JField::setShort(JObject* obj, jshort s){
                set(obj,new JPrimitiveShort(s));
            }

            JString* JField::toString(){
                JStringBuilder* builder=new JStringBuilder();
                builder->append(getType()->getName())->append(" ");
                builder->append(getDeclaringClass()->getName())->append(".")->append(getName());
                return builder->toString();
            }

            JField::~JField(){
            }
        }
    }
}
