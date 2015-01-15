#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

using jcpp::native::api::NativeString;

namespace jcpp {
	namespace lang {

		static jcpp::lang::JClass* primitiveCharArray = null;
		jcpp::lang::JClass* JPrimitiveCharArray::getClazz() {
			if (primitiveCharArray == null) {
				primitiveCharArray = JPrimitiveArray::getClazz(JPrimitiveChar::getClazz());
			}
			return primitiveCharArray;
		}

		JPrimitiveCharArray::JPrimitiveCharArray(jint len) : JPrimitiveArray(JPrimitiveChar::getClazz(), len) {
			data = new jchar[len];
			for(jint i = 0; i < len; i++) {
				data[i] = 0;
			}
		}

		JPrimitiveCharArray::JPrimitiveCharArray(jint len, const jchar * data) : JPrimitiveArray(JPrimitiveChar::getClazz(), len){
			this->data = new jchar[len];
			for (jint i=0; i<len; i++) {
				this->data[i] = data[i];
			}
		}

		JPrimitiveCharArray::JPrimitiveCharArray(JPrimitiveCharArray* a) : JPrimitiveArray(a) {
			data = new jchar[a->size()];
			for (jint i = 0; i < size(); i++) {
				data[i] = a->data[i];
			}
		}

		jchar* JPrimitiveCharArray::getArray(){
			return data;
		}

		jchar JPrimitiveCharArray::getChar(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return data[i];
		}

		void JPrimitiveCharArray::setChar(jint i, jchar value) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			data[i] = value;
		}

		JObject* JPrimitiveCharArray::get(jint i) {
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			return new JPrimitiveChar(data[i]);
		}

		void JPrimitiveCharArray::set(jint i, JObject* value) {
			checkType(value);
			if ((i < 0) || (i > size() - 1)) {
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(i)));
			}
			JPrimitiveChar* b = dynamic_cast<JPrimitiveChar*>(value);
			data[i] = b->get();
		}

		void JPrimitiveCharArray::finalize() {
			delete[] data;
		}

		JPrimitiveCharArray* JPrimitiveCharArray::clone() {
			return new JPrimitiveCharArray(this);
		}

		JPrimitiveCharArray::~JPrimitiveCharArray() {
		}
	}
}
