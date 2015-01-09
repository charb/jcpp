#ifndef JCPP_NATIVE_API_NATIVEENDIAN
#define JCPP_NATIVE_API_NATIVEENDIAN

#include "jcpp/native/api/NativeAPI.h"

namespace jcpp {
	namespace native {
		namespace api {

			class JCPP_EXPORT NativeEndian {

			private:
				static jbool bigEndian;

			public:

				static jbool isBigEndian();

				/**
				 * The jint primitive will be written to 4 jbytes
				 * with Big Endian memory format and will be written
				 * into the buffer at the specified index.
				 *
				 * Return value: index + 4 will be returned
				 */
				static jint write(jint value, jbyte * buf, jint index);

				/**
				 * The jshort primitive will be written to 2 jbytes
				 * with Big Endian memory format and will be written
				 * into the buffer at the specified index.
				 *
				 * Return value: index + 2 will be returned
				 */
				static jint write(jshort value, jbyte * buf, jint index);

				/**
				 * The jlong primitive will be written to 8 jbytes
				 * with Big Endian memory format and will be written
				 * into the buffer at the specified index.
				 *
				 * Return value: index + 8 will be returned
				 */
				static jint write(jlong value, jbyte * buf, jint index);

				/**
				 * The jfloat primitive will be written to 4 jbytes
				 * with Big Endian memory format and will be written
				 * into the buffer at the specified index.
				 *
				 * Return value: index + 4 will be returned
				 */
				static jint write(jfloat value, jbyte * buf, jint index);

				/**
				 * The jdouble primitive will be written to 8 jbytes
				 * with Big Endian memory format and will be written
				 * into the buffer at the specified index.
				 *
				 * Return value: index + 8 will be returned
				 */
				static jint write(jdouble value, jbyte * buf, jint index);

				/**
				 * The jchar primitive will be written to 2 jbytes
				 * with Big Endian memory format and will be written
				 * into the buffer at the specified index.
				 *
				 * Return value: index + 2 will be returned
				 */
				static jint write(jchar value, jbyte * buf, jint index);

				/**
				 * The jbool primitive will be written to 1 jbyte
				 * and will be written into the buffer at the specified
				 * index.
				 *
				 * Return value: index + 1 will be returned
				 */
				static jint write(jbool value, jbyte * buf, jint index);

				/**
				 * A jint primitive will be read from the specified buffer
				 * at the specified index using the Big Endian memory format.
				 * The value will be stored at the given pointer.
				 *
				 * Return value: index + 4 will be returned
				 */
				static jint read(jint * pvalue, jbyte * buf, jint index);

				/**
				 * A jshort primitive will be read from the specified buffer
				 * at the specified index using the Big Endian memory format.
				 * The value will be stored at the given pointer.
				 *
				 * Return value: index + 2 will be returned
				 */
				static jint read(jshort * pvalue, jbyte * buf, jint index);

				/**
				 * A jlong primitive will be read from the specified buffer
				 * at the specified index using the Big Endian memory format.
				 * The value will be stored at the given pointer.
				 *
				 * Return value: index + 8 will be returned
				 */
				static jint read(jlong * pvalue, jbyte * buf, jint index);

				/**
				 * A jfloat primitive will be read from the specified buffer
				 * at the specified index using the Big Endian memory format.
				 * The value will be stored at the given pointer.
				 *
				 * Return value: index + 4 will be returned
				 */
				static jint read(jfloat * pvalue, jbyte * buf, jint index);

				/**
				 * A jdouble primitive will be read from the specified buffer
				 * at the specified index using the Big Endian memory format.
				 * The value will be stored at the given pointer.
				 *
				 * Return value: index + 8 will be returned
				 */
				static jint read(jdouble * pvalue, jbyte * buf, jint index);

				/**
				 * A jchar primitive will be read from the specified buffer
				 * at the specified index using the Big Endian memory format.
				 * The value will be stored at the given pointer.
				 *
				 * Return value: index + 2 will be returned
				 */
				static jint read(jchar * pvalue, jbyte * buf, jint index);

				/**
				 * A jbool primitive will be read from the specified buffer
				 * at the specified index. The value will be stored at the
				 * given pointer.
				 *
				 * Return value: index + 1 will be returned
				 */
				static jint read(jbool * pvalue, jbyte * buf, jint index);
			};

		}
	}
}

#endif
