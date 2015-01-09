#include "jcpp/native/api/NativeEndian.h"

namespace jcpp {
	namespace native {
		namespace api {

			const int ENDIAN_TEST_VARIABLE = 1;

			jbool NativeEndian::bigEndian = (*(char*) &ENDIAN_TEST_VARIABLE) == 0;

			jbool NativeEndian::isBigEndian() {
				return bigEndian;
			}

			jint NativeEndian::write(jint value, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) &value;
				if (bigEndian) {
					buf[index] = p[0];
					buf[index + 1] = p[1];
					buf[index + 2] = p[2];
					buf[index + 3] = p[3];
				} else {
					buf[index] = p[3];
					buf[index + 1] = p[2];
					buf[index + 2] = p[1];
					buf[index + 3] = p[0];
				}
				return index + 4;
			}

			jint NativeEndian::write(jshort value, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) &value;
				if (bigEndian) {
					buf[index] = p[0];
					buf[index + 1] = p[1];
				} else {
					buf[index] = p[1];
					buf[index + 1] = p[0];
				}
				return index + 2;
			}

			jint NativeEndian::write(jlong value, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) &value;
				if (bigEndian) {
					buf[index] = p[0];
					buf[index + 1] = p[1];
					buf[index + 2] = p[2];
					buf[index + 3] = p[3];
					buf[index + 4] = p[4];
					buf[index + 5] = p[5];
					buf[index + 6] = p[6];
					buf[index + 7] = p[7];
				} else {
					buf[index] = p[7];
					buf[index + 1] = p[6];
					buf[index + 2] = p[5];
					buf[index + 3] = p[4];
					buf[index + 4] = p[3];
					buf[index + 5] = p[2];
					buf[index + 6] = p[1];
					buf[index + 7] = p[0];
				}
				return index + 8;
			}

			jint NativeEndian::write(jfloat value, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) &value;
				if (bigEndian) {
					buf[index] = p[0];
					buf[index + 1] = p[1];
					buf[index + 2] = p[2];
					buf[index + 3] = p[3];
				} else {
					buf[index] = p[3];
					buf[index + 1] = p[2];
					buf[index + 2] = p[1];
					buf[index + 3] = p[0];
				}
				return index + 4;
			}

			jint NativeEndian::write(jdouble value, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) &value;
				if (bigEndian) {
					buf[index] = p[0];
					buf[index + 1] = p[1];
					buf[index + 2] = p[2];
					buf[index + 3] = p[3];
					buf[index + 4] = p[4];
					buf[index + 5] = p[5];
					buf[index + 6] = p[6];
					buf[index + 7] = p[7];
				} else {
					buf[index] = p[7];
					buf[index + 1] = p[6];
					buf[index + 2] = p[5];
					buf[index + 3] = p[4];
					buf[index + 4] = p[3];
					buf[index + 5] = p[2];
					buf[index + 6] = p[1];
					buf[index + 7] = p[0];
				}
				return index + 8;
			}

			jint NativeEndian::write(jchar value, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) &value;
				if (bigEndian) {
					buf[index] = p[0];
					buf[index + 1] = p[1];
				} else {
					buf[index] = p[1];
					buf[index + 1] = p[0];
				}
				return index + 2;
			}

			jint NativeEndian::write(jbool value, jbyte * buf, jint index) {
				buf[index] = value ? 1 : 0;
				return index + 1;
			}

			jint NativeEndian::read(jint * pvalue, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) pvalue;
				if (bigEndian) {
					p[0] = buf[index];
					p[1] = buf[index + 1];
					p[2] = buf[index + 2];
					p[3] = buf[index + 3];
				} else {
					p[0] = buf[index + 3];
					p[1] = buf[index + 2];
					p[2] = buf[index + 1];
					p[3] = buf[index];
				}
				return index + 4;
			}

			jint NativeEndian::read(jshort * pvalue, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) pvalue;
				if (bigEndian) {
					p[0] = buf[index];
					p[1] = buf[index + 1];
				} else {
					p[0] = buf[index + 1];
					p[1] = buf[index];
				}
				return index + 2;
			}

			jint NativeEndian::read(jlong * pvalue, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) pvalue;
				if (bigEndian) {
					p[0] = buf[index];
					p[1] = buf[index + 1];
					p[2] = buf[index + 2];
					p[3] = buf[index + 3];
					p[4] = buf[index + 4];
					p[5] = buf[index + 5];
					p[6] = buf[index + 6];
					p[7] = buf[index + 7];
				} else {
					p[0] = buf[index + 7];
					p[1] = buf[index + 6];
					p[2] = buf[index + 5];
					p[3] = buf[index + 4];
					p[4] = buf[index + 3];
					p[5] = buf[index + 2];
					p[6] = buf[index + 1];
					p[7] = buf[index];
				}
				return index + 8;
			}

			jint NativeEndian::read(jfloat * pvalue, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) pvalue;
				if (bigEndian) {
					p[0] = buf[index];
					p[1] = buf[index + 1];
					p[2] = buf[index + 2];
					p[3] = buf[index + 3];
				} else {
					p[0] = buf[index + 3];
					p[1] = buf[index + 2];
					p[2] = buf[index + 1];
					p[3] = buf[index];
				}
				return index + 4;
			}

			jint NativeEndian::read(jdouble * pvalue, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) pvalue;
				if (bigEndian) {
					p[0] = buf[index];
					p[1] = buf[index + 1];
					p[2] = buf[index + 2];
					p[3] = buf[index + 3];
					p[4] = buf[index + 4];
					p[5] = buf[index + 5];
					p[6] = buf[index + 6];
					p[7] = buf[index + 7];
				} else {
					p[0] = buf[index + 7];
					p[1] = buf[index + 6];
					p[2] = buf[index + 5];
					p[3] = buf[index + 4];
					p[4] = buf[index + 3];
					p[5] = buf[index + 2];
					p[6] = buf[index + 1];
					p[7] = buf[index];
				}
				return index + 8;
			}

			jint NativeEndian::read(jchar * pvalue, jbyte * buf, jint index) {
				jbyte *p = (jbyte *) pvalue;
				if (bigEndian) {
					p[0] = buf[index];
					p[1] = buf[index + 1];
				} else {
					p[0] = buf[index + 1];
					p[1] = buf[index];
				}
				return index + 2;
			}

			jint NativeEndian::read(jbool * pvalue, jbyte * buf, jint index) {
				if (buf[index] == 0) {
					pvalue[0] = false;
				} else {
					pvalue[0] = true;
				}
				return index + 1;
			}

		}
	}
}
