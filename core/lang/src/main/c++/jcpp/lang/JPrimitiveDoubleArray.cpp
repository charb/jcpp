#include "jcpp/lang/JPrimitiveDoubleArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		static jcpp::lang::JClass* primitiveDoubleArray = null;
		jcpp::lang::JClass* JPrimitiveDoubleArray::getClazz() {
			if (primitiveDoubleArray == null) {
				primitiveDoubleArray = JPrimitiveArray::getClazz(JPrimitiveDouble::getClazz());
			}
			return primitiveDoubleArray;
		}

		JPrimitiveDoubleArray::JPrimitiveDoubleArray(jint len) : JPrimitiveArray(JPrimitiveDouble::getClazz(), len) {
			data = new jdouble[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0.0;
			}
		}

		JPrimitiveDoubleArray::JPrimitiveDoubleArray(JPrimitiveDoubleArray* a) : JPrimitiveArray(a) {
			data = new jdouble[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jdouble JPrimitiveDoubleArray::getDouble(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveDoubleArray::setDouble(jint i, jdouble value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveDoubleArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveDouble(data[i]);
		}

		void JPrimitiveDoubleArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveDouble* b = dynamic_cast<JPrimitiveDouble*>(value);
			data[i] = b->get();
		}

		void JPrimitiveDoubleArray::finalize() {
			delete[] data;
		}

		JPrimitiveDoubleArray* JPrimitiveDoubleArray::clone() {
			return new JPrimitiveDoubleArray(this);
		}

		JPrimitiveDoubleArray::~JPrimitiveDoubleArray() {
		}
	}
}
