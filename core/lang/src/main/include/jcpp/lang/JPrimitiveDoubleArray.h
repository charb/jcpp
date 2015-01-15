#ifndef JCPP_LANG_JPRIMITIVE_DOUBLE_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_DOUBLE_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {

		// @IgnoreReflection()
		class JCPP_EXPORT JPrimitiveDoubleArray: public JPrimitiveArray {

		protected:
			jdouble* data;
		public:
			JPrimitiveDoubleArray(jint len);

			JPrimitiveDoubleArray(JPrimitiveDoubleArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jdouble getDouble(jint i);

			virtual void setDouble(jint i, jdouble value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveDoubleArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveDoubleArray();
		};
	}
}

#endif
