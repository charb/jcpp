#ifndef JCPP_LANG_JPRIMITIVE_BYTE_ARRAY_H
#define JCPP_LANG_JPRIMITIVE_BYTE_ARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"

namespace jcpp {
	namespace io{
		class JFileInputStream;
		class JFileOutputStream;
		class JNativeInputStream;
		class JNativeOutputStream;
	}
	namespace net{
		class JInetAddress;
	}
	namespace lang {

		// @IgnoreReflection()
		class JCPP_EXPORT JPrimitiveByteArray: public JPrimitiveArray {
		private:
			static jcpp::lang::JClass* primitiveByteArray;

		protected:
			jbyte* data;
			jbyte* getArray();

			friend class jcpp::io::JFileInputStream;
			friend class jcpp::io::JFileOutputStream;
			friend class jcpp::io::JNativeInputStream;
			friend class jcpp::io::JNativeOutputStream;
			friend class jcpp::net::JInetAddress;;

		public:
			JPrimitiveByteArray(jint len);

			JPrimitiveByteArray(JPrimitiveByteArray* a);

			static jcpp::lang::JClass* getClazz();

			virtual jbyte getByte(jint i);

			virtual void setByte(jint i, jbyte value);

			virtual JObject* get(jint i);

			virtual void set(jint i, JObject* value);

			virtual JPrimitiveByteArray* clone();

			virtual void finalize();

			virtual ~JPrimitiveByteArray();
		};
	}
}

#endif
