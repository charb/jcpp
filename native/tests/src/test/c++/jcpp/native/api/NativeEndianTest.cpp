#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeEndian.h"

using namespace jcpp::native::api;

#define TEST_NAME "Native Endian"

void printByteBuffer(jbyte * original, jbyte * buf, int max) {
	unsigned char *optr = (unsigned char *) original;
	unsigned char *ptr = (unsigned char *) buf;
	for (int i = 0; i < max; i++) {
		logInfo("Byte @ index [%d]\t %x -> %x", i, optr[i], ptr[i]);
	}
	printf("\n");
}

jbool jintTest() {
	jbyte buf[4];

	logInfo("Testing jint conversion. Original value = 0x 01 12 A3 80");
	jint value = 0x0112A380;

	NativeEndian::write(value, buf, 0);
	printByteBuffer((jbyte *) &value, buf, 4);

	if ((buf[0] != 1) || (buf[1] != 18) || (buf[2] != -93) || (buf[3] != -128)) {
		logError("jint conversion TO multibyte Big Endian failed");
		return false;
	}

	jint readValue = 0;
	NativeEndian::read(&readValue, buf, 0);
	if (readValue != value) {
		logError("jint conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

jbool jshortTest() {
	jbyte buf[2];

	logInfo("Testing jshort conversion. Original value = 0x B9 12");
	jshort value = 0xB912;

	NativeEndian::write(value, buf, 0);
	printByteBuffer((jbyte *) &value, buf, 2);

	if ((buf[0] != -71) || (buf[1] != 18)) {
		logError("jshort conversion TO multibyte Big Endian failed");
		return false;
	}

	jshort readValue = 0;
	NativeEndian::read(&readValue, buf, 0);
	if (readValue != value) {
		logError("jshort conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

jbool jlongTest() {
	jbyte buf[8];

	logInfo("Testing jlong conversion. Original value = 0x 01 12 A3 80 B9 F7 55 D2");
	jlong value = 0x0112A380B9F755D2LL;

	NativeEndian::write(value, buf, 0);
	printByteBuffer((jbyte *) &value, buf, 8);

	if ((buf[0] != 1) || (buf[1] != 18) || (buf[2] != -93) || (buf[3] != -128) || (buf[4] != -71) || (buf[5] != -9) || (buf[6] != 85) || (buf[7] != -46)) {
		logError("jlong conversion TO multibyte Big Endian failed");
		return false;
	}

	jlong readValue = 0;
	NativeEndian::read(&readValue, buf, 0);
	if (readValue != value) {
		logError("jlong conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

jbool jfloatTest() {
	jbyte buf[4];

	logInfo("Testing jfloat conversion. Original value = 0x 01 12 A3 80");
	jfloat value = 0;
	jint * p = reinterpret_cast<jint *>(&value);
	*p = 0x0112A380;

	logInfo("jfloat value = %e", value);

	NativeEndian::write(value, buf, 0);
	printByteBuffer((jbyte *) p, buf, 4);

	if ((buf[0] != 1) || (buf[1] != 18) || (buf[2] != -93) || (buf[3] != -128)) {
		logError("jfloat conversion TO multibyte Big Endian failed");
		return false;
	}

	jfloat readValue = 0;
	NativeEndian::read(&readValue, buf, 0);
	jfloat dif = (readValue - value) > 0 ? (readValue - value) : (value - readValue);
	if (dif > 0.0000001) {
		logError("jfloat conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

jbool jdoubleTest() {
	jbyte buf[8];

	logInfo("Testing jdouble conversion. Original value = 0x 01 12 A3 80 B9 F7 55 D2");
	jdouble value = 0;
	jlong * p = reinterpret_cast<jlong *>(&value);
	*p = 0x0112A380B9F755D2LL;

	logInfo("jdouble value = %e", value);

	NativeEndian::write(value, buf, 0);
	printByteBuffer((jbyte *) p, buf, 8);

	if ((buf[0] != 1) || (buf[1] != 18) || (buf[2] != -93) || (buf[3] != -128) || (buf[4] != -71) || (buf[5] != -9) || (buf[6] != 85) || (buf[7] != -46)) {
		logError("jdouble conversion TO multibyte Big Endian failed");
		return false;
	}

	jdouble readValue = 0;
	NativeEndian::read(&readValue, buf, 0);
	jdouble dif = (readValue - value) > 0 ? (readValue - value) : (value - readValue);
	if (dif > 0.0000001) {
		logError("jdouble conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

jbool jcharTest() {
	jbyte buf[2];

	logInfo("Testing jchar conversion. Original value = 0x B9 12");
	jchar value = 0xB912;

	NativeEndian::write(value, buf, 0);
	printByteBuffer((jbyte *) &value, buf, 2);

	if ((buf[0] != -71) || (buf[1] != 18)) {
		logError("jchar conversion TO multibyte Big Endian failed");
		return false;
	}

	jchar readValue = 0;
	NativeEndian::read(&readValue, buf, 0);
	if (readValue != value) {
		logError("jchar conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

jbool jboolTest() {
	jbyte buf[1];

	logInfo("Testing jbool conversion. Original value = true");
	jbool value = true;

	NativeEndian::write(value, buf, 0);
	printByteBuffer(reinterpret_cast<jbyte *>(&value), buf, 1);

	if ((buf[0] != 1)) {
		logError("jbool conversion TO multibyte Big Endian failed");
		return false;
	}

	jbool readValue = false;
	NativeEndian::read(&readValue, buf, 0);
	if (readValue != value) {
		logError("jbool conversion FROM multibyte Big Endian failed");
		return false;
	}

	return true;
}

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	if (NativeEndian::isBigEndian()) {
		logInfo("Machine is Big Endian\n");
	} else {
		logInfo("Machine is Little Endian\n");
	}

	if (!jintTest()) {
		FAIL_TEST(TEST_NAME);
	}
	if (!jshortTest()) {
		FAIL_TEST(TEST_NAME);
	}
	if (!jlongTest()) {
		FAIL_TEST(TEST_NAME);
	}

	if (!jfloatTest()) {
		FAIL_TEST(TEST_NAME);
	}
	if (!jdoubleTest()) {
		FAIL_TEST(TEST_NAME);
	}

	if (!jcharTest()) {
		FAIL_TEST(TEST_NAME);
	}
	if (!jboolTest()) {
		FAIL_TEST(TEST_NAME);
	}

	PASS_TEST(TEST_NAME)
}
