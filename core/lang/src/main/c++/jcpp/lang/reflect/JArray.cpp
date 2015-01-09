#include "jcpp/lang/reflect/JArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JPrimitiveDoubleArray.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveShortArray.h"
#include "jcpp/lang/JIllegalArgumentException.h"

using namespace jcpp::lang;
using jcpp::native::api::NativeString;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JArrayClass : public jcpp::lang::JClass{
                public:
                    JArrayClass():jcpp::lang::JClass(){
                        canonicalName=new JString("java.lang.reflect.Array");
                        name=new JString("java.lang.reflect.Array");
                        simpleName=new JString("Array");
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return JObject::getClazz();
                    }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JArray::getClazz(){
                if (clazz==null){
                    clazz=new JArrayClass();
                }
                return clazz;
            }

            JObject* JArray::newInstance(jcpp::lang::JClass* componentType, jint length){
            	if (componentType->isPrimitive()) {
					if (componentType == JPrimitiveBoolean::getClazz()) {
						return new JPrimitiveBooleanArray(length);
					} else if (componentType == JPrimitiveByte::getClazz()) {
						return new JPrimitiveByteArray(length);
					} else if (componentType == JPrimitiveChar::getClazz()) {
						return new JPrimitiveCharArray(length);
					} else if (componentType == JPrimitiveDouble::getClazz()) {
						return new JPrimitiveDoubleArray(length);
					} else if (componentType == JPrimitiveFloat::getClazz()) {
						return new JPrimitiveFloatArray(length);
					} else if (componentType == JPrimitiveLong::getClazz()) {
						return new JPrimitiveLongArray(length);
					} else if (componentType == JPrimitiveShort::getClazz()) {
						return new JPrimitiveShortArray(length);
					} else if (componentType == JPrimitiveInt::getClazz()) {
						return new JPrimitiveIntArray(length);
					} else {
						throw new JIllegalArgumentException(new JString("Unknown Primitive Class"));
					}
            	}
                return new JPrimitiveObjectArray(componentType,length);
            }

            jint JArray::getLength(JObject* array){
                JPrimitiveArray* pa=dynamic_cast<JPrimitiveArray*>(array);
                return pa->size();
            }

            JObject* JArray::get(JObject* array, jint index){
                JPrimitiveArray* pa=dynamic_cast<JPrimitiveArray*>(array);
                return pa->get(index);
            }

            jbool JArray::getBoolean(JObject* array, jint index){
                JPrimitiveBooleanArray* pb=dynamic_cast<JPrimitiveBooleanArray*>(array);
                return pb->getBoolean(index);
            }

            jbyte JArray::getByte(JObject* array, jint index){
                JPrimitiveByteArray* pb=dynamic_cast<JPrimitiveByteArray*>(array);
                return pb->getByte(index);
            }

            jchar JArray::getChar(JObject* array, jint index){
                JPrimitiveCharArray* pb=dynamic_cast<JPrimitiveCharArray*>(array);
                return pb->getChar(index);
            }

            jshort JArray::getShort(JObject* array, jint index){
                JPrimitiveShortArray* pb=dynamic_cast<JPrimitiveShortArray*>(array);
                return pb->getShort(index);
            }

            jint JArray::getInt(JObject* array, jint index){
                JPrimitiveIntArray* pb=dynamic_cast<JPrimitiveIntArray*>(array);
                return pb->getInt(index);
            }
            
            jlong JArray::getLong(JObject* array, jint index){
                JPrimitiveLongArray* pb=dynamic_cast<JPrimitiveLongArray*>(array);
                return pb->getLong(index);
            }

            jfloat JArray::getFloat(JObject* array, jint index){
                JPrimitiveFloatArray* pb=dynamic_cast<JPrimitiveFloatArray*>(array);
                return pb->getFloat(index);
            }

            jdouble JArray::getDouble(JObject* array, jint index){
                JPrimitiveDoubleArray* pb=dynamic_cast<JPrimitiveDoubleArray*>(array);
                return pb->getDouble(index);
            }

            void JArray::set(JObject* array, jint index, JObject* value){
                JPrimitiveArray* pa=dynamic_cast<JPrimitiveArray*>(array);
                pa->set(index,value);
            }

            void JArray::setBoolean(JObject* array, jint index, jbool z){
                JPrimitiveBooleanArray* pa=dynamic_cast<JPrimitiveBooleanArray*>(array);
                pa->setBoolean(index,z);
            }
        
            void JArray::setByte(JObject* array, jint index, jbyte b){
                JPrimitiveByteArray* pa=dynamic_cast<JPrimitiveByteArray*>(array);
                pa->setByte(index,b);
            }

            void JArray::setChar(JObject* array, jint index, jchar c){
                JPrimitiveCharArray* pa=dynamic_cast<JPrimitiveCharArray*>(array);
                pa->setChar(index,c);
            }

            void JArray::setShort(JObject* array, jint index, jshort s){
                JPrimitiveShortArray* pa=dynamic_cast<JPrimitiveShortArray*>(array);
                pa->setShort(index,s);
            }

            void JArray::setInt(JObject* array, jint index, jint i){
                JPrimitiveIntArray* pa=dynamic_cast<JPrimitiveIntArray*>(array);
                pa->setInt(index,i);
            }

            void JArray::setLong(JObject* array, jint index, jlong l){
                JPrimitiveLongArray* pa=dynamic_cast<JPrimitiveLongArray*>(array);
                pa->setLong(index,l);
            }

            void JArray::setFloat(JObject* array, jint index, jfloat f){
                JPrimitiveFloatArray* pa=dynamic_cast<JPrimitiveFloatArray*>(array);
                pa->setFloat(index,f);
            }
    
            void JArray::setDouble(JObject* array, jint index, jdouble d){
                JPrimitiveDoubleArray* pa=dynamic_cast<JPrimitiveDoubleArray*>(array);
                pa->setDouble(index,d);
            }

            JArray::~JArray(){
            }
        }
    }
}

