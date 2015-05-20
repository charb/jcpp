#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		jcpp::lang::JClass* JPrimitiveLongArray::primitiveLongArray = null;
		jcpp::lang::JClass* JPrimitiveLongArray::getClazz() {
			if (primitiveLongArray == null) {
				primitiveLongArray = JPrimitiveArray::getClazz(JPrimitiveLong::getClazz());
			}
			return primitiveLongArray;
		}

		JPrimitiveLongArray::JPrimitiveLongArray(jint len) : JPrimitiveArray(JPrimitiveLong::getClazz(), len) {
			data = new jlong[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0;
			}
		}

		JPrimitiveLongArray::JPrimitiveLongArray(JPrimitiveLongArray* a) : JPrimitiveArray(a) {
			data = new jlong[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jlong JPrimitiveLongArray::getLong(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveLongArray::setLong(jint i, jlong value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveLongArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveLong(data[i]);
		}

		void JPrimitiveLongArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveLong* b = dynamic_cast<JPrimitiveLong*>(value);
			data[i] = b->get();
		}

		void JPrimitiveLongArray::finalize() {
			delete[] data;
		}

		JPrimitiveLongArray* JPrimitiveLongArray::clone() {
			return new JPrimitiveLongArray(this);
		}

		JPrimitiveLongArray::~JPrimitiveLongArray() {
		}
	}
}
