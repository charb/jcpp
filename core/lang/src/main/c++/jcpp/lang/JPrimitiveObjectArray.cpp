#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JMap.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveShort.h"

using namespace jcpp::util;
using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		JPrimitiveObjectArray::JPrimitiveObjectArray(jcpp::lang::JClass* arrayClass, jint len) : JPrimitiveArray(arrayClass, len) {
			objects = new JObject*[len];

			if (arrayClass->isPrimitive()) {
				throw new JIllegalArgumentException(new JString(NativeString("Should not use JPrimitiveObjectArray for primitive type: ") + arrayClass->getName()->getNativeString()));
			}
			for (jint i = 0; i < size(); i++) {
				objects[i] = null;
			}
		}

		JPrimitiveObjectArray::JPrimitiveObjectArray(JPrimitiveObjectArray* a) : JPrimitiveArray(a) {
			objects = new JObject*[a->size()];
			for (jint i = 0; i < size(); i++) {
				set(i, a->get(i));
			}
		}

		jcpp::lang::JClass* JPrimitiveObjectArray::getClazz(jcpp::lang::JClass* componentType) {
			return JPrimitiveArray::getClazz(componentType);
		}

		jcpp::lang::JClass* JPrimitiveObjectArray::getClazz() {
			return JPrimitiveArray::getClazz(JObject::getClazz());
		}

		JObject* JPrimitiveObjectArray::get(jint i) {
			return objects[i];
		}

		void JPrimitiveObjectArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			objects[i] = value;
		}

		void JPrimitiveObjectArray::finalize() {
			delete[] objects;
		}

		JPrimitiveObjectArray* JPrimitiveObjectArray::clone() {
			return new JPrimitiveObjectArray(this);
		}

		jbool JPrimitiveObjectArray::equals(JObject* o){
			if (o==null || o->getClass()!=getClass()){
				return false;
			}
			JPrimitiveObjectArray* other=dynamic_cast<JPrimitiveObjectArray*>(o);
			if (size()!=other->size()){
				return false;
			}
			for (jint i=0;i<size();i++){
				JObject* o1=get(i);
				JObject* o2=other->get(i);
				if (o1==null){
					if (o2!=null){
						return false;
					}
				}else{
					if (o2==null){
						return false;
					}
					if (!o1->equals(o2)){
						return false;
					}
				}
			}
            return true;
		}

		JPrimitiveObjectArray::~JPrimitiveObjectArray() {
		}
	}
}
