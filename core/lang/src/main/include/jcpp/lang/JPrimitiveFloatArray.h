#ifndef JCPP_LANG_JPRIMITIVE_FLOAT_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_FLOAT_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {

		// @IgnoreReflection()
		class JCPP_EXPORT JPrimitiveFloatArray: public JPrimitiveArray {
		private:
			static jcpp::lang::JClass* primitiveFloatArray;
		protected:
			jfloat* data;
		public:
			JPrimitiveFloatArray(jint len);

			JPrimitiveFloatArray(JPrimitiveFloatArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jfloat getFloat(jint i);

			virtual void setFloat(jint i, jfloat value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveFloatArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveFloatArray();
		};
	}
}

#endif
