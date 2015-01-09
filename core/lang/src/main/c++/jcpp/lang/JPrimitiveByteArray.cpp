#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		static jcpp::lang::JClass* primitiveByteArray = null;
		jcpp::lang::JClass* JPrimitiveByteArray::getClazz() {
			if (primitiveByteArray == null) {
				primitiveByteArray = JPrimitiveArray::getClazz(JPrimitiveByte::getClazz());
			}
			return primitiveByteArray;
		}

		JPrimitiveByteArray::JPrimitiveByteArray(jint len) : JPrimitiveArray(JPrimitiveByte::getClazz(), len) {
			data = new jbyte[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0;
			}
		}

		JPrimitiveByteArray::JPrimitiveByteArray(JPrimitiveByteArray* a) : JPrimitiveArray(a) {
			data = new jbyte[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jbyte* JPrimitiveByteArray::getArray() {
			return data;
		}

		jbyte JPrimitiveByteArray::getByte(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveByteArray::setByte(jint i, jbyte value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveByteArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveByte(data[i]);
		}

		void JPrimitiveByteArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveByte* b = dynamic_cast<JPrimitiveByte*>(value);
			data[i] = b->get();
		}

		void JPrimitiveByteArray::finalize() {
			delete[] data;
		}

		JPrimitiveByteArray* JPrimitiveByteArray::clone() {
			return new JPrimitiveByteArray(this);
		}

		JPrimitiveByteArray::~JPrimitiveByteArray() {
		}
	}
}
