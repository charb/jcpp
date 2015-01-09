#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeString.h"

#include <iostream>

#define TEST_NAME "Native String"

using namespace jcpp::native::api;

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	NativeString s = "test";
	ASSERT_M(s.length(), 4, "Tested C String Constructor", "C String Constructor created a String with wrong length", TEST_NAME)

	NativeString ws = L"test";
	ASSERT_M(ws.length(), 4, "Tested Wide Char String String Constructor", "Wide Char String Constructor created a String with wrong length", TEST_NAME)

	std::string str("test");
	NativeString cpps = str;
	ASSERT_M(cpps.length(), 4, "Tested CPP String Constructor", "CPP String Constructor created a String with wrong length", TEST_NAME)

	std::wstring wstr(L"test");
	NativeString wcpps = wstr;
	ASSERT_M(wcpps.length(), 4, "Tested Wide Char CPP String Constructor", "Wide Char CPP String Constructor created a String with wrong length", TEST_NAME)

	std::string sToString = s.getString();
	ASSERT_M(sToString, str, "Tested Creating a CPP String", "Creating a CPP String from the Native String created an un-equal String", TEST_NAME)

	std::wstring wsToString = s.getWString();
	ASSERT_M(wsToString, wstr, "Tested Creating a Wide Char CPP String", "Creating a Wide Char CPP String from the Native String created an un-equal String", TEST_NAME)

	ASSERT_M(s, "test", "Tested == with C String", "Failed to test for equality with a C String", TEST_NAME)
	ASSERT_M(s, L"test", "Tested == with Wide Char String", "Failed to test for equality with a Wide Char String", TEST_NAME)
	ASSERT_M(s, str, "Tested == with CPP String", "Failed to test for equality with a CPP String", TEST_NAME)
	ASSERT_M(s, wstr, "Tested == with Wide Char CPP String", "Failed to test for equality with a Wide Char CPP String", TEST_NAME)

	ASSERT_NE_M(s, "tes", "Tested != with C String", "Failed to test for in-equality with a C String", TEST_NAME)
	ASSERT_NE_M(s, L"tes", "Tested != with Wide Char String", "Failed to test for in-equality with a Wide Char String", TEST_NAME)
	std::string str2("tes");
	ASSERT_NE_M(s, str2, "Tested != with CPP String", "Failed to test for in-equality with a CPP String", TEST_NAME)
	std::wstring wstr2(L"tes");
	ASSERT_NE_M(s, wstr2, "Tested != with Wide Char CPP String", "Failed to test for in-equality with a Wide Char CPP String", TEST_NAME)

	ASSERT_EM(s.isEmpty(), false, "String returned true for empty check while it is not empty", TEST_NAME)
	NativeString emptyString("");
	ASSERT_EM(emptyString.isEmpty(), true, "String returned false for empty check while it is empty", TEST_NAME)

	ASSERT_EM(s.charAt(1), (jchar )'e', "Failed to get a specific character from the String", TEST_NAME)

	jchar buf[4];
	s.getChars(1, 2, buf, 1);
	ASSERT_EM(buf[1], (jchar )'e', "Failed to get a set of characters from the String", TEST_NAME)
	ASSERT_EM(buf[2], (jchar )'s', "Failed to get a set of characters from the String", TEST_NAME)

	NativeString ss("testtest");
	ASSERT_EM(ss.indexOf((jchar ) 'e', 3), 5, "Failed to get a the index of a character from the String", TEST_NAME)
	ASSERT_EM(ss.lastIndexOf((jchar ) 'e', ss.length()), 5, "Failed to get a the last index of a character from the String", TEST_NAME)

	ASSERT_EM(ss.indexOf(s, 1), 4, "Failed to get a the index of a string from the String", TEST_NAME)
	ASSERT_EM(ss.lastIndexOf(s, 3), 0, "Failed to get a the last index of a string from the String", TEST_NAME)

	ASSERT_EM(ss.startsWith(s), true, "Failed to test is a String starts with another String", TEST_NAME)
	ASSERT_EM(ss.endsWith(s), true, "Failed to test is a String ends with another String", TEST_NAME)

	NativeString sub = ss.substring(4);
	ASSERT_EM(sub, s, "Failed to create a correct substring", TEST_NAME)

	NativeString concatStr = s.concat(s);
	ASSERT_EM(concatStr, ss, "Failed to concatinate 2 Strings", TEST_NAME)

	NativeString rr("resrresr");
	NativeString replacedString = ss.replace('t', 'r');
	ASSERT_EM(replacedString, rr, "Failed to replcae a character in a String", TEST_NAME)

	NativeString spaceStr("  test  ");
	NativeString trimedStr = spaceStr.trim();
	ASSERT_EM(trimedStr, s, "Failed to trim a String", TEST_NAME)

	NativeString rev("tset");
	NativeString reversed = s.reverse();
	ASSERT_EM(reversed, rev, "Failed to reverse a String", TEST_NAME)

	NativeString clone = s.clone();
	ASSERT_EM(clone, s, "Failed to clone a String", TEST_NAME)

	std::cout << "Testing cout << " << s << std::endl;

	PASS_TEST(TEST_NAME)
}
