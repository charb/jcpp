#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		static jcpp::lang::JClass* primitiveBooleanArray = null;
		jcpp::lang::JClass* JPrimitiveBooleanArray::getClazz() {
			if (primitiveBooleanArray == null) {
				primitiveBooleanArray = JPrimitiveArray::getClazz(JPrimitiveBoolean::getClazz());
			}
			return primitiveBooleanArray;
		}

		JPrimitiveBooleanArray::JPrimitiveBooleanArray(jint len) : JPrimitiveArray(JPrimitiveBoolean::getClazz(), len) {
			data = new jbool[len];
			for(jint i = 0; i < len; i++) {
				data[i] = false;
			}
		}

		JPrimitiveBooleanArray::JPrimitiveBooleanArray(JPrimitiveBooleanArray* a) : JPrimitiveArray(a) {
			data = new jbool[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jbool JPrimitiveBooleanArray::getBoolean(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveBooleanArray::setBoolean(jint i, jbool value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveBooleanArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveBoolean(data[i]);
		}

		void JPrimitiveBooleanArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveBoolean* b = dynamic_cast<JPrimitiveBoolean*>(value);
			data[i] = b->get();
		}

		void JPrimitiveBooleanArray::finalize() {
			delete[] data;
		}

		JPrimitiveBooleanArray* JPrimitiveBooleanArray::clone() {
			return new JPrimitiveBooleanArray(this);
		}

		JPrimitiveBooleanArray::~JPrimitiveBooleanArray() {
		}
	}
}
