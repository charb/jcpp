#include "jcpp/lang/JPrimitiveShortArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		static jcpp::lang::JClass* primitiveShortArray = null;
		jcpp::lang::JClass* JPrimitiveShortArray::getClazz() {
			if (primitiveShortArray == null) {
				primitiveShortArray = JPrimitiveArray::getClazz(JPrimitiveShort::getClazz());
			}
			return primitiveShortArray;
		}

		JPrimitiveShortArray::JPrimitiveShortArray(jint len) : JPrimitiveArray(JPrimitiveShort::getClazz(), len) {
			data = new jshort[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0;
			}
		}

		JPrimitiveShortArray::JPrimitiveShortArray(JPrimitiveShortArray* a) : JPrimitiveArray(a) {
			data = new jshort[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jshort JPrimitiveShortArray::getShort(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveShortArray::setShort(jint i, jshort value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveShortArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveShort(data[i]);
		}

		void JPrimitiveShortArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveShort* b = dynamic_cast<JPrimitiveShort*>(value);
			data[i] = b->get();
		}

		void JPrimitiveShortArray::finalize() {
			delete[] data;
		}

		JPrimitiveShortArray* JPrimitiveShortArray::clone() {
			return new JPrimitiveShortArray(this);
		}

		JPrimitiveShortArray::~JPrimitiveShortArray() {
		}
	}
}
