#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/api/NativeException.h"
#include <cstring>
#include <cwchar>
#include <sstream>
#include <stdlib.h>

#if defined(_MSC_VER)
#define strtoll _strtoi64
#endif

namespace jcpp {
	namespace native {
		namespace api {

			char * NativeString::className = "jcpp::native::api::NativeString";

			NativeString::NativeString() {
				size = 0;
				value = null;
			}

			NativeString::~NativeString() {
				if(value) {
					delete[] value;
					value = null;
				}
				size = 0;
			}

			//TODO might be bugged if str is UTF8
			NativeString::NativeString(const char * str) {
				size = strlen(str);
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = str[i];
				}
			}

			NativeString::NativeString(const wchar_t* wstr) {
				size = wcslen(wstr);
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = wstr[i];
				}
			}

			NativeString::NativeString(const std::string & str) {
				size = str.length();
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = str[i];
				}
			}

			NativeString::NativeString(const std::wstring & wstr) {
				size = wstr.length();
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = wstr[i];
				}
			}

			NativeString::NativeString(const NativeString& str) {
				size = str.size;
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = str.value[i];
				}
			}

			NativeString::NativeString(jchar c) {
				size = 1;
				value = new jchar[1];
				value[0] = c;
			}

			NativeString::NativeString(const char* str, jint offset, jint length) {
				size = length;
				value = new jchar[size];

				for (jint i = 0; i < length; i++) {
					value[i] = str[offset + i];
				}
			}

			NativeString::NativeString(const wchar_t* wstr, jint offset, jint length) {
				size = length;
				value = new jchar[size];

				for (jint i = 0; i < length; i++) {
					value[i] = wstr[offset + i];
				}
			}

			NativeString::NativeString(const jchar* c, jint offset, jint length) {
				size = length;
				value = new jchar[size];

				for (jint i = 0; i < length; i++) {
					value[i] = c[offset + i];
				}
			}

			NativeString::NativeString(jchar * value, jint size) {
				this->value = value;
				this->size = size;
			}

			jint NativeString::length() const {
				return size;
			}

			jbool NativeString::isEmpty() const {
				return size == 0;
			}

			jchar NativeString::charAt(jint index) const {
				if (index < 0 || index >= size) {
					return 0;
				}
				return value[index];
			}

			jchar* NativeString::getChars() const {
				return value;
			}

			void NativeString::getChars(jint srcBegin, jint srcEnd, jchar * dst, jint dstBegin) const {
				if ((srcBegin < 0) || (srcBegin >= size)) {
					throw NativeException(className, "getChars", OUT_OF_BOUND_EXCEPTION, "Out of bound src begin");
				}

				if (srcEnd < 0 || srcEnd >= size) {
					throw NativeException(className, "getChars", OUT_OF_BOUND_EXCEPTION, "Out of bound src end");
				}

				if (dstBegin < 0) {
					throw NativeException(className, "getChars", ILLEGAL_ARGUMENT_EXCEPTION, "Negative destination begin index");
				}

				for (jint i = srcBegin; i <= srcEnd; i++) {
					dst[dstBegin++] = value[i];
				}
			}

			std::string NativeString::getString() const {
				std::string str("");
				if (size == 0) {
					return str;
				}

				jint bufferSize = size < 1024 ? size : 1024;

				char *buf = new char[bufferSize];

				jint i = 0, index = 0;
				while (index < size) {
					for (i = 0; (i < bufferSize) && (i < size); i++) {
						buf[i] = value[index++];
					}
					if (i > 0) {
						str.append(buf, i);
					}
				}

				delete[] buf;

				str.resize(size);
				return str;
			}

			std::wstring NativeString::getWString() const {
				std::wstring wstr(L"");

				if (size == 0) {
					return wstr;
				}

				jint bufferSize = size < 1024 ? size : 1024;

				wchar_t * buf = new wchar_t[bufferSize];

				jint i = 0, index = 0;
				while (index < size) {
					for (i = 0; (i < bufferSize) && (i < size); i++) {
						buf[i] = value[index++];
					}
					if (i > 0) {
						wstr.append(buf, i);
					}
				}
				delete[] buf;

				wstr.resize(size);
				return wstr;
			}

			jint NativeString::indexOf(jchar ch) const {
				return indexOf(ch, 0);
			}

			jint NativeString::indexOf(jchar ch, jint fromIndex) const {
				for (jint i = fromIndex; i < size; i++) {
					if (value[i] == ch) {
						return i;
					}
				}
				return -1;
			}

			jint NativeString::lastIndexOf(jchar ch) const {
				return lastIndexOf(ch, size - 1);
			}

			jint NativeString::lastIndexOf(jchar ch, jint fromIndex) const {
				fromIndex = fromIndex >= size ? size - 1 : fromIndex;
				for (jint i = fromIndex; i >= 0; i--) {
					if (value[i] == ch) {
						return i;
					}
				}
				return -1;
			}

			jint NativeString::indexOf(const NativeString& str) const {
				return indexOf(str, 0);
			}

			jint NativeString::indexOf(const NativeString& str, jint fromIndex) const {
				if (fromIndex >= size) {
					return (str.size == 0 ? size : -1);
				}
				if (fromIndex < 0) {
					fromIndex = 0;
				}
				if (str.size == 0) {
					return fromIndex;
				}

				jchar first = str.value[0];
				jint max = (size - str.size);

				for (jint i = fromIndex; i <= max; i++) {
					if (value[i] != first) {
						while (++i <= max && value[i] != first)
							;
					}

					if (i <= max) {
						jint j = i + 1;
						jint end = j + str.size - 1;
						for (jint k = 1; j < end && value[j] == str.value[k]; j++, k++)
							;

						if (j == end) {
							return i;
						}
					}
				}
				return -1;
			}

			jint NativeString::lastIndexOf(const NativeString& str) const {
				return lastIndexOf(str, size - 1);
			}

			jint NativeString::lastIndexOf(const NativeString& str, jint fromIndex) const {
				jint rightIndex = size - str.size;
				if (fromIndex < 0) {
					return -1;
				}
				if (fromIndex > rightIndex) {
					fromIndex = rightIndex;
				}
				if (str.size == 0) {
					return fromIndex;
				}

				jint strLastIndex = str.size - 1;
				jchar strLastChar = str.value[strLastIndex];
				jint min = str.size - 1;
				jint i = min + fromIndex;

				startSearchForLastChar: while (true) {
					while (i >= min && value[i] != strLastChar) {
						i--;
					}
					if (i < min) {
						return -1;
					}
					jint j = i - 1;
					jint start = j - (str.size - 1);
					jint k = strLastIndex - 1;

					while (j > start) {
						if (value[j--] != str.value[k--]) {
							i--;
							goto startSearchForLastChar;
						}
					}
					return start + 1;
				}
				return -1;
			}

			jbool NativeString::startsWith(const jchar ch) const {
				return size > 0 && value[0] == ch;
			}

			jbool NativeString::startsWith(const NativeString& prefix) const {
				return startsWith(prefix, 0);
			}

			jbool NativeString::startsWith(const NativeString& prefix, jint toffset) const {
				jint to = toffset;
				jint po = 0;
				jint pc = prefix.size;
				if ((toffset < 0) || (toffset > size - pc)) {
					return false;
				}
				while (--pc >= 0) {
					if (value[to++] != prefix.value[po++]) {
						return false;
					}
				}
				return true;
			}

			jbool NativeString::endsWith(const jchar ch) const {
				return size > 0 && value[size - 1] == ch;
			}

			jbool NativeString::endsWith(const NativeString& suffix) const {
				return startsWith(suffix, size - suffix.size);
			}

			NativeString NativeString::substring(jint beginIndex) const {
				return substring(beginIndex, size);
			}

			NativeString NativeString::substring(jint beginIndex, jint endIndex) const {
				if ((beginIndex < 0) || (beginIndex > size)) {
					throw NativeException(className, "substring", OUT_OF_BOUND_EXCEPTION, "Out of bound begin index");
				}
				if ((endIndex < 0) || (endIndex > size) || (endIndex < beginIndex)) {
					throw NativeException(className, "substring", OUT_OF_BOUND_EXCEPTION, "Out of bound end index");
				}
				jint newSize = endIndex - beginIndex;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = value[beginIndex + i];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::concat(const NativeString& str) const {
				jint newSize = size + str.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : str.value[i - size];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::replace(jchar oldChar, jchar newChar) const {
				jchar * newValue = new jchar[size];
				for (jint i = 0; i < size; i++) {
					newValue[i] = value[i] == oldChar ? newChar : value[i];
				}
				return NativeString(newValue, size);
			}

			NativeString NativeString::trim() const {
				jint len = size;
				jint st = 0;

				while ((st < len) && (value[st] <= ' ')) {
					st++;
				}
				while ((st < len) && (value[len - 1] <= ' ')) {
					len--;
				}
				return ((st > 0) || (len < size)) ? substring(st, len) : clone();
			}

			NativeString NativeString::reverse() const {
				jchar * newValue = new jchar[size];
				for (jint i = 0; i < size; i++) {
					newValue[i] = value[size - i - 1];
				}
				return NativeString(newValue, size);
			}

			NativeString NativeString::clone() const {
				jchar * newValue = new jchar[size];
				for (jint i = 0; i < size; i++) {
					newValue[i] = value[i];
				}
				return NativeString(newValue, size);
			}

			// TODO Implement for different Locals
			NativeString NativeString::toLowerCase() const {
				jchar * newValue = new jchar[size];
				for (jint i = 0; i < size; i++) {
					newValue[i] = (65 <= value[i]) && (value[i] <= 90) ? value[i] + 32 : value[i];
				}
				return NativeString(newValue, size);
			}

			// TODO Implement for different Locals
			NativeString NativeString::toUpperCase() const {
				jchar * newValue = new jchar[size];
				for (jint i = 0; i < size; i++) {
					newValue[i] = (97 <= value[i]) && (value[i] <= 122) ? value[i] - 32 : value[i];
				}
				return NativeString(newValue, size);
			}

			// TODO Implement for different Locals
			jbool NativeString::equalsIgnoreCase(const NativeString& other) const {
				if (size != other.size) {
					return false;
				}
				jchar * otherValue = other.value;
				for (jint i = 0; i < size; i++) {
					if (value[i] != otherValue[i]) {
						if (((97 <= value[i]) && (value[i] <= 122)) && ((65 <= otherValue[i]) && (otherValue[i] <= 90)) && ((value[i] - 32) == otherValue[i])) {
							continue;
						}
						if (((65 <= value[i]) && (value[i] <= 90)) && ((97 <= otherValue[i]) && (otherValue[i] <= 122)) && (value[i] == (otherValue[i] - 32))) {
							continue;
						}
						return false;
					}
				}
				return true;
			}

			jchar NativeString::operator[](jint index) const {
				if (index < 0 || index >= size) {
					throw NativeException(className, "operator[]", OUT_OF_BOUND_EXCEPTION, "Out of bound index");
				}
				return value[index];
			}

			NativeString& NativeString::operator=(const NativeString& other) {
				if(value) {
					delete[] value;
					value = null;
				}
				size = other.size;
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = other.value[i];
				}

				return *this;
			}

			NativeString& NativeString::operator=(const char* str) {
				if(value) {
					delete[] value;
					value = null;
				}
				size = strlen(str);
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = str[i];
				}

				return *this;
			}

			NativeString& NativeString::operator=(const wchar_t* wstr) {
				if(value) {
					delete[] value;
					value = null;
				}
				size = wcslen(wstr);
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = wstr[i];
				}

				return *this;
			}

			NativeString& NativeString::operator=(const std::string& str) {
				if(value) {
					delete[] value;
					value = null;
				}
				size = str.length();
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = str[i];
				}

				return *this;
			}

			NativeString& NativeString::operator=(const std::wstring& wstr) {
				if(value) {
					delete[] value;
					value = null;
				}
				size = wstr.length();
				value = new jchar[size];

				for (jint i = 0; i < size; i++) {
					value[i] = wstr[i];
				}

				return *this;
			}

			NativeString NativeString::operator+(const NativeString& other) const {
				jint newSize = size + other.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : other.value[i - size];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::operator+(const char* str) const {
				jint strSize = strlen(str);
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : str[i - size];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::operator+(const wchar_t* wstr) const {
				jint strSize = wcslen(wstr);
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : wstr[i - size];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::operator+(const std::string& str) const {
				jint strSize = str.length();
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : str[i - size];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::operator+(const std::wstring& wstr) const {
				jint strSize = wstr.length();
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : wstr[i - size];
				}
				return NativeString(newValue, newSize);
			}

			NativeString NativeString::operator+(const jbool b) const {
				return *this + (b ? "true" : "false");
			}

			NativeString NativeString::operator+(const jint i) const {
				std::stringstream out;
				out << i;
				return *this + out.str();
			}

			NativeString NativeString::operator+(const jshort s) const {
				std::stringstream out;
				out << s;
				return *this + out.str();
			}

			NativeString NativeString::operator+(const jlong l) const {
				std::stringstream out;
				out << l;
				return *this + out.str();
			}

			NativeString NativeString::operator+(const jfloat f) const {
				std::stringstream out;
				out << f;
				return *this + out.str();
			}

			NativeString NativeString::operator+(const jdouble d) const {
				std::stringstream out;
				out << d;
				return *this + out.str();
			}

			NativeString NativeString::operator+(const jbyte b) const {
				std::stringstream out;
				out << (jint) b;
				return *this + out.str();
			}

			void NativeString::operator+=(const NativeString& other) {
				jint newSize = size + other.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : other.value[i - size];
				}
				if(value) {
					delete[] value;
					value = null;
				}
				value = newValue;
				size = newSize;
			}

			void NativeString::operator+=(const char* str) {
				jint strSize = strlen(str);
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : str[i - size];
				}
				if(value) {
					delete[] value;
					value = null;
				}
				value = newValue;
				size = newSize;
			}

			void NativeString::operator+=(const wchar_t* wstr) {
				jint strSize = wcslen(wstr);
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : wstr[i - size];
				}
				if(value) {
					delete[] value;
					value = null;
				}
				value = newValue;
				size = newSize;
			}

			void NativeString::operator+=(const std::string& str) {
				jint strSize = str.length();
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : str[i - size];
				}
				if(value) {
					delete[] value;
					value = null;
				}
				value = newValue;
				size = newSize;
			}

			void NativeString::operator+=(const std::wstring& wstr) {
				jint strSize = wstr.length();
				jint newSize = size + strSize;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < size ? value[i] : wstr[i - size];
				}
				if(value) {
					delete[] value;
					value = null;
				}
				value = newValue;
				size = newSize;
			}

			void NativeString::operator+=(const jbool b) {
				operator+=(b ? "true" : "false");
			}

			void NativeString::operator+=(const jint i) {
				std::stringstream out;
				out << i;
				operator+=(out.str());
			}

			void NativeString::operator+=(const jshort s) {
				std::stringstream out;
				out << s;
				operator+=(out.str());
			}

			void NativeString::operator+=(const jlong l) {
				std::stringstream out;
				out << l;
				operator+=(out.str());
			}

			void NativeString::operator+=(const jfloat f) {
				std::stringstream out;
				out << f;
				operator+=(out.str());
			}

			void NativeString::operator+=(const jdouble d) {
				std::stringstream out;
				out << d;
				operator+=(out.str());
			}

			void NativeString::operator+=(const jbyte b) {
				std::stringstream out;
				out << (jint) b;
				operator+=(out.str());
			}

			jbool NativeString::operator==(const NativeString& other) const {
				if (size != other.size) {
					return false;
				}
				jchar * otherValue = other.value;
				for (jint i = 0; i < size; i++) {
					if (value[i] != otherValue[i]) {
						return false;
					}
				}
				return true;
			}

			jbool NativeString::operator==(const char* str) const {
				if ((str == null) || (size != (jint) strlen(str))) {
					return false;
				}
				for (jint i = 0; i < size; i++) {
					if (value[i] != str[i]) {
						return false;
					}
				}
				return true;
			}

			jbool NativeString::operator==(const wchar_t* wstr) const {
				if ((wstr == null) || (size != (jint) wcslen(wstr))) {
					return false;
				}
				for (jint i = 0; i < size; i++) {
					if (value[i] != wstr[i]) {
						return false;
					}
				}
				return true;
			}

			jbool NativeString::operator==(const std::string& str) const {
				if (size != (jint) str.length()) {
					return false;
				}
				for (jint i = 0; i < size; i++) {
					if (value[i] != str[i]) {
						return false;
					}
				}
				return true;
			}

			jbool NativeString::operator==(const std::wstring& wstr) const {
				if (size != (jint) wstr.length()) {
					return false;
				}
				for (jint i = 0; i < size; i++) {
					if (value[i] != wstr[i]) {
						return false;
					}
				}
				return true;
			}

			jbool NativeString::operator!=(const NativeString& other) const {
				return !(*this == other);
			}

			jbool NativeString::operator!=(const char* str) const {
				return !(*this == str);
			}

			jbool NativeString::operator!=(const wchar_t* wstr) const {
				return !(*this == wstr);
			}

			jbool NativeString::operator!=(const std::string& str) const {
				return !(*this == str);
			}

			jbool NativeString::operator!=(const std::wstring& wstr) const {
				return !(*this == wstr);
			}

			jbool NativeString::operator<(const NativeString& other) const {
				int lim = size < other.size ? size : other.size;
				int k = 0;
				while (k < lim) {
					char c1 = value[k];
					char c2 = other.value[k];
					if (c1 != c2) {
						return c1 < c2;
					}
					k++;
				}
				return size < other.size;
			}

			jbool NativeString::toJbool() const {
				return equalsIgnoreCase(NativeString("true"));
			}

			jint NativeString::toJint() const {
				return atoi(getString().c_str());
			}

			jshort NativeString::toJshort() const {
				return (jshort) atoi(getString().c_str());
			}

			jlong NativeString::toJlong() const {
				return (jlong) strtoll(getString().c_str(), NULL, 10);
			}

			jfloat NativeString::toJfloat() const {
				return (jfloat) atof(getString().c_str());
			}

			jdouble NativeString::toJdouble() const {
				return atof(getString().c_str());
			}

			jbyte NativeString::toJbyte() const {
				return (jbyte) atoi(getString().c_str());
			}

			NativeString NativeString::valueOf(jbool b) {
				return b ? NativeString("true") : NativeString("false");
			}

			NativeString NativeString::valueOf(jint i) {
				std::stringstream out;
				out << i;
				return NativeString(out.str());
			}

			NativeString NativeString::valueOf(jshort s) {
				std::stringstream out;
				out << s;
				return NativeString(out.str());
			}

			NativeString NativeString::valueOf(jlong l) {
				std::stringstream out;
				out << l;
				return NativeString(out.str());
			}

			NativeString NativeString::valueOf(jfloat f) {
				std::stringstream out;
				out << f;
				return NativeString(out.str());
			}

			NativeString NativeString::valueOf(jdouble d) {
				std::stringstream out;
				out << d;
				return NativeString(out.str());
			}

			NativeString NativeString::valueOf(jbyte b) {
				std::stringstream out;
				out << (jint) b;
				return NativeString(out.str());
			}

			JCPP_EXPORT NativeString operator+(const char* str, const NativeString& other) {
				jint strSize = strlen(str);
				jint newSize = strSize + other.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < strSize ? str[i] : other.value[i - strSize];
				}
				return NativeString(newValue, newSize);
			}

			JCPP_EXPORT NativeString operator+(const wchar_t* wstr, const NativeString& other) {
				jint strSize = wcslen(wstr);
				jint newSize = strSize + other.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < strSize ? wstr[i] : other.value[i - strSize];
				}
				return NativeString(newValue, newSize);
			}

			JCPP_EXPORT NativeString operator+(const std::string& str, const NativeString& other) {
				jint strSize = str.length();
				jint newSize = strSize + other.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < strSize ? str[i] : other.value[i - strSize];
				}
				return NativeString(newValue, newSize);
			}

			JCPP_EXPORT NativeString operator+(const std::wstring& wstr, const NativeString& other) {
				jint strSize = wstr.length();
				jint newSize = strSize + other.size;
				jchar * newValue = new jchar[newSize];
				for (jint i = 0; i < newSize; i++) {
					newValue[i] = i < strSize ? wstr[i] : other.value[i - strSize];
				}
				return NativeString(newValue, newSize);
			}

			JCPP_EXPORT NativeString operator+(const jbool b, const NativeString& other) {
				return other + (b ? "true" : "false");
			}

			JCPP_EXPORT NativeString operator+(const jint i, const NativeString& other) {
				std::stringstream out;
				out << i;
				return other + out.str();
			}

			JCPP_EXPORT NativeString operator+(const jshort s, const NativeString& other) {
				std::stringstream out;
				out << s;
				return other + out.str();
			}

			JCPP_EXPORT NativeString operator+(const jlong l, const NativeString& other) {
				std::stringstream out;
				out << l;
				return other + out.str();
			}

			JCPP_EXPORT NativeString operator+(const jfloat f, const NativeString& other) {
				std::stringstream out;
				out << f;
				return other + out.str();
			}

			JCPP_EXPORT NativeString operator+(const jdouble d, const NativeString& other) {
				std::stringstream out;
				out << d;
				return other + out.str();
			}

			JCPP_EXPORT NativeString operator+(const jbyte b, const NativeString& other) {
				std::stringstream out;
				out << (jint) b;
				return other + out.str();
			}

			JCPP_EXPORT jbool operator==(const char* str, const NativeString& other) {
				return other == str;
			}

			JCPP_EXPORT jbool operator==(const wchar_t* wstr, const NativeString& other) {
				return other == wstr;
			}

			JCPP_EXPORT jbool operator==(const std::string& str, const NativeString& other) {
				return other == str;
			}

			JCPP_EXPORT jbool operator==(const std::wstring& wstr, const NativeString& other) {
				return other == wstr;
			}

			JCPP_EXPORT jbool operator!=(const char* str, const NativeString& other) {
				return other != str;
			}

			JCPP_EXPORT jbool operator!=(const wchar_t* wstr, const NativeString& other) {
				return other != wstr;
			}

			JCPP_EXPORT jbool operator!=(const std::string& str, const NativeString& other) {
				return other != str;
			}

			JCPP_EXPORT jbool operator!=(const std::wstring& wstr, const NativeString& other) {
				return other != wstr;
			}

			std::ostream& operator<<(std::ostream& out, const NativeString& str) {
				jint size = str.length();
				jchar * value = str.getChars();
				for (jint i = 0; i < size; i++) {
					out << ((char) value[i]);
				}
				return out;
			}

			std::wostream& operator<<(std::wostream& out, const NativeString& wstr) {
				jint size = wstr.length();
				jchar * value = wstr.getChars();
				for (jint i = 0; i < size; i++) {
					out << ((wchar_t) value[i]);
				}
				return out;
			}

		}
	}
}
