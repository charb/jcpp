#ifndef JCPP_LANG_JPRIMITIVE_CHAR_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_CHAR_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {
		class JCPP_EXPORT JPrimitiveCharArray: public JPrimitiveArray {
		protected:
			jchar* data;
			jchar* getArray();

		public:
			JPrimitiveCharArray(jint len);

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
