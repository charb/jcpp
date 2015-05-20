#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		jcpp::lang::JClass* JPrimitiveFloatArray::primitiveFloatArray = null;
		jcpp::lang::JClass* JPrimitiveFloatArray::getClazz() {
			if (primitiveFloatArray == null) {
				primitiveFloatArray = JPrimitiveArray::getClazz(JPrimitiveFloat::getClazz());
			}
			return primitiveFloatArray;
		}

		JPrimitiveFloatArray::JPrimitiveFloatArray(jint len) : JPrimitiveArray(JPrimitiveFloat::getClazz(), len) {
			data = new jfloat[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0.0;
			}
		}

		JPrimitiveFloatArray::JPrimitiveFloatArray(JPrimitiveFloatArray* a) : JPrimitiveArray(a) {
			data = new jfloat[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jfloat JPrimitiveFloatArray::getFloat(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveFloatArray::setFloat(jint i, jfloat value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveFloatArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveFloat(data[i]);
		}

		void JPrimitiveFloatArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveFloat* b = dynamic_cast<JPrimitiveFloat*>(value);
			data[i] = b->get();
		}

		void JPrimitiveFloatArray::finalize() {
			delete[] data;
		}

		JPrimitiveFloatArray* JPrimitiveFloatArray::clone() {
			return new JPrimitiveFloatArray(this);
		}

		JPrimitiveFloatArray::~JPrimitiveFloatArray() {
		}
	}
}
