#ifndef JCPP_LANG_JPRIMITIVE_LONG_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_LONG_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {
		class JCPP_EXPORT JPrimitiveLongArray: public JPrimitiveArray {
		protected:
			jlong* data;
		public:
			JPrimitiveLongArray(jint len);

			JPrimitiveLongArray(JPrimitiveLongArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jlong getLong(jint i);

			virtual void setLong(jint i, jlong value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveLongArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveLongArray();
		};
	}
}

#endif
