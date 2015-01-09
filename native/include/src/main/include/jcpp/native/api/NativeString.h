#ifndef JCPP_NATIVE_API_NATIVESTRING
#define JCPP_NATIVE_API_NATIVESTRING

#include "jcpp/native/api/NativeInclude.h"
#include <string>
#include <iostream>

namespace jcpp {
	namespace native {
		namespace api {

			class JCPP_EXPORT NativeString {

				friend JCPP_EXPORT NativeString operator+(const char*, const NativeString&);
				friend JCPP_EXPORT NativeString operator+(const wchar_t* wstr, const NativeString&);
				friend JCPP_EXPORT NativeString operator+(const std::string&, const NativeString&);
				friend JCPP_EXPORT NativeString operator+(const std::wstring&, const NativeString&);

			private:
				static char * className;

				jchar * value;
				jint size;

				NativeString(jchar * value, jint size);

			public:

				NativeString();
				~NativeString();

				NativeString(const NativeString& original);

				NativeString(const char* str);
				NativeString(const wchar_t* wstr);

				NativeString(const std::string& str);
				NativeString(const std::wstring& wstr);

				NativeString(jchar c);
				NativeString(const char* str, jint offset, jint length);
				NativeString(const wchar_t* wstr, jint offset, jint length);
				NativeString(const jchar* c, jint offset, jint length);

				jint length() const;
				jbool isEmpty() const;

				jchar charAt(jint index) const;
				void getChars(jint cBegin, jint srcEnd, jchar * dst, jint dstBegin) const;

				jint indexOf(jchar ch) const;
				jint indexOf(jchar ch, jint fromIndex) const;
				jint lastIndexOf(jchar ch) const;
				jint lastIndexOf(jchar ch, jint fromIndex) const;

				jint indexOf(const NativeString& str) const;
				jint indexOf(const NativeString& str, jint fromIndex) const;
				jint lastIndexOf(const NativeString& str) const;
				jint lastIndexOf(const NativeString& str, jint fromIndex) const;

				jbool startsWith(const jchar ch) const;
				jbool startsWith(const NativeString& prefix) const;
				jbool startsWith(const NativeString& prefix, jint toffset) const;

				jbool endsWith(const jchar ch) const;
				jbool endsWith(const NativeString& suffix) const;

				NativeString substring(jint beginIndex) const;
				NativeString substring(jint beginIndex, jint endIndex) const;

				NativeString concat(const NativeString& str) const;
				NativeString replace(jchar oldChar, jchar newChar) const;

				NativeString trim() const;
				NativeString reverse() const;
				NativeString clone() const;
				NativeString toLowerCase() const;
				NativeString toUpperCase() const;

				jbool equalsIgnoreCase(const NativeString& str) const;

				jchar* getChars() const;
				std::string getString() const;
				std::wstring getWString() const;

				jchar operator[](jint index) const;

				NativeString& operator=(const NativeString& other);
				NativeString& operator=(const char* str);
				NativeString& operator=(const wchar_t* wstr);
				NativeString& operator=(const std::string& str);
				NativeString& operator=(const std::wstring& wstr);

				NativeString operator+(const NativeString& other) const;
				NativeString operator+(const char* str) const;
				NativeString operator+(const wchar_t* wstr) const;
				NativeString operator+(const std::string& str) const;
				NativeString operator+(const std::wstring& wstr) const;
				NativeString operator+(const jbool b) const;
				NativeString operator+(const jint i) const;
				NativeString operator+(const jshort s) const;
				NativeString operator+(const jlong l) const;
				NativeString operator+(const jfloat f) const;
				NativeString operator+(const jdouble d) const;
				NativeString operator+(const jbyte b) const;

				void operator+=(const NativeString& other);
				void operator+=(const char* str);
				void operator+=(const wchar_t* wstr);
				void operator+=(const std::string& str);
				void operator+=(const std::wstring& wstr);
				void operator+=(const jbool b);
				void operator+=(const jint i);
				void operator+=(const jshort s);
				void operator+=(const jlong l);
				void operator+=(const jfloat f);
				void operator+=(const jdouble d);
				void operator+=(const jbyte b);

				jbool operator==(const NativeString& other) const;
				jbool operator==(const char* str) const;
				jbool operator==(const wchar_t* wstr) const;
				jbool operator==(const std::string& str) const;
				jbool operator==(const std::wstring& wstr) const;

				jbool operator!=(const NativeString& other) const;
				jbool operator!=(const char* str) const;
				jbool operator!=(const wchar_t* wstr) const;
				jbool operator!=(const std::string& str) const;
				jbool operator!=(const std::wstring& wstr) const;

				jbool operator<(const NativeString& other) const;

				jbool toJbool() const;
				jint toJint() const;
				jshort toJshort() const;
				jlong toJlong() const;
				jfloat toJfloat() const;
				jdouble toJdouble() const;
				jbyte toJbyte() const;

				static NativeString valueOf(jbool b);
				static NativeString valueOf(jint i);
				static NativeString valueOf(jshort s);
				static NativeString valueOf(jlong l);
				static NativeString valueOf(jfloat f);
				static NativeString valueOf(jdouble d);
				static NativeString valueOf(jbyte b);

			};

			JCPP_EXPORT NativeString operator+(const char* str, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const wchar_t* wstr, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const std::string& str, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const std::wstring& wstr, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jbool b, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jint i, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jshort s, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jlong l, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jfloat f, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jdouble d, const NativeString& other);
			JCPP_EXPORT NativeString operator+(const jbyte b, const NativeString& other);

			JCPP_EXPORT jbool operator==(const char* str, const NativeString& other);
			JCPP_EXPORT jbool operator==(const wchar_t* wstr, const NativeString& other);
			JCPP_EXPORT jbool operator==(const std::string& str, const NativeString& other);
			JCPP_EXPORT jbool operator==(const std::wstring& wstr, const NativeString& other);

			JCPP_EXPORT jbool operator!=(const char* str, const NativeString& other);
			JCPP_EXPORT jbool operator!=(const wchar_t* wstr, const NativeString& other);
			JCPP_EXPORT jbool operator!=(const std::string& str, const NativeString& other);
			JCPP_EXPORT jbool operator!=(const std::wstring& wstr, const NativeString& other);

			JCPP_EXPORT std::ostream& operator<<(std::ostream& out, const NativeString& str);
			JCPP_EXPORT std::wostream& operator<<(std::wostream& out, const NativeString& wstr);

		}
	}
}

#endif
