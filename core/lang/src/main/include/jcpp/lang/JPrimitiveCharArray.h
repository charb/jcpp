#ifndef JCPP_LANG_JPRIMITIVE_CHAR_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_CHAR_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {

		// @IgnoreReflection()
		class JCPP_EXPORT JPrimitiveCharArray: public JPrimitiveArray {
		private:
			static jcpp::lang::JClass* primitiveCharArray;
		protected:
			jchar* data;
			jchar* getArray();

		public:
			JPrimitiveCharArray(jint len);

			JPrimitiveCharArray(jint len, const jchar* data);

			JPrimitiveCharArray(JPrimitiveCharArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jchar getChar(jint i);

			virtual void setChar(jint i, jchar value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveCharArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveCharArray();

			friend class JString;
		};
	}
}

#endif
