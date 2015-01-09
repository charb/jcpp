#ifndef JCPP_LANG_JPRIMITIVE_BOOLEAN_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_BOOLEAN_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {
		class JCPP_EXPORT JPrimitiveBooleanArray: public JPrimitiveArray {
		protected:
			jbool* data;
		public:
			JPrimitiveBooleanArray(jint len);

			JPrimitiveBooleanArray(JPrimitiveBooleanArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jbool getBoolean(jint i);

			virtual void setBoolean(jint i, jbool value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveBooleanArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveBooleanArray();
		};
	}
}

#endif
