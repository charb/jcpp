#ifndef JCPP_LANG_JPRIMITIVE_INT_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_INT_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {

		// @IgnoreReflection()
		class JCPP_EXPORT JPrimitiveIntArray: public JPrimitiveArray {
		protected:
			jint* data;
		public:
			JPrimitiveIntArray(jint len);

			JPrimitiveIntArray(JPrimitiveIntArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jint getInt(jint i);

			virtual void setInt(jint i, jint value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveIntArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveIntArray();
		};
	}
}

#endif
