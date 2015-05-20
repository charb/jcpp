#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		jcpp::lang::JClass* JPrimitiveIntArray::primitiveIntArray = null;
		jcpp::lang::JClass* JPrimitiveIntArray::getClazz() {
			if (primitiveIntArray == null) {
				primitiveIntArray = JPrimitiveArray::getClazz(JPrimitiveInt::getClazz());
			}
			return primitiveIntArray;
		}

		JPrimitiveIntArray::JPrimitiveIntArray(jint len) : JPrimitiveArray(JPrimitiveInt::getClazz(), len) {
			data = new jint[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0;
			}
		}

		JPrimitiveIntArray::JPrimitiveIntArray(JPrimitiveIntArray* a) : JPrimitiveArray(a) {
			data = new jint[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jint JPrimitiveIntArray::getInt(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveIntArray::setInt(jint i, jint value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveIntArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveInt(data[i]);
		}

		void JPrimitiveIntArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveInt* b = dynamic_cast<JPrimitiveInt*>(value);
			data[i] = b->get();
		}

		void JPrimitiveIntArray::finalize() {
			delete[] data;
		}

		JPrimitiveIntArray* JPrimitiveIntArray::clone() {
			return new JPrimitiveIntArray(this);
		}

		JPrimitiveIntArray::~JPrimitiveIntArray() {
		}
	}
}
