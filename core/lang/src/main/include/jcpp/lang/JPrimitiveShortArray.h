#ifndef JCPP_LANG_JPRIMITIVE_SHORT_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_SHORT_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace lang {
		class JCPP_EXPORT JPrimitiveShortArray: public JPrimitiveArray {
		protected:
			jshort* data;
		public:
			JPrimitiveShortArray(jint len);

			JPrimitiveShortArray(JPrimitiveShortArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jshort getShort(jint i);

			virtual void setShort(jint i, jshort value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveShortArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveShortArray();
		};
	}
}

#endif
