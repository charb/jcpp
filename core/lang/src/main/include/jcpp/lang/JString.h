#ifndef JCPP_LANG_JSTRING_H
#define JCPP_LANG_JSTRING_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/native/api/NativeString.h"

using jcpp::native::api::NativeString;

namespace jcpp{
    namespace net{
        class JURLClassLoader;
    }

    namespace io{
    	class JFileOutputStream;
    	class JFileInputStream;
    	class JFile;
    }

    namespace util{
        class JHashMap;
        class JComparator;
    }

    namespace net{
    	class JInetAddress;
    }

    namespace lang{
        class JPrimitiveCharArray;
        class JPrimitiveByteArray;
        class JDouble;
        class JFloat;
        class JInteger;
        class JLong;
        class JPrimitiveCharArray;
        class JPrimitiveLongArray;
        class JPrimitiveFloatArray;
        class JPrimitiveShortArray;
        class JPrimitiveDoubleArray;
        class JPrimitiveBooleanArray;
        class JPrimitiveIntArray;
        class JPrimitiveByteArray;
        class JPrimitiveLongArray;
        class JPrimitiveObjectArray;
        class JClassLoader;
        class JThread;
        class JSystem;
        class JThrowable;
        class JProcessBuilder;
        class JProcess;
        class JAbstractStringBuilder;

        class JCPP_EXPORT JString : public JObject, public JComparable, public JCloneable, public jcpp::io::JSerializable, public JCharSequence{
        private:
        	static void checkBounds(JPrimitiveByteArray* bytes, jint offset, jint length);

        protected:
            NativeString nativeString;

            NativeString getNativeString();

            JString(const NativeString& string);

            static JString* staticIntern(JString* s);
        public:

            static jint hashCode(JString* s);

            static jint compare(JString* s1,JString* s2);

            static JString* NULL_STRING;

            static JString* valueOf(JObject* obj);

            static JString* valueOf(JPrimitiveCharArray* data);

            static JString* valueOf(JPrimitiveCharArray* data, jint offset, jint count);

            static JString* valueOf(jbool b);

            static JString* valueOf(jchar c);

            static JString* valueOf(jint i);

            static JString* valueOf(jlong l);

            static JString* valueOf(jfloat f);

            static JString* valueOf(jdouble d);

            JString();

            JString(string str);

            JString(JString* str);

            JString(const char* c);

            JString(JPrimitiveCharArray* chars);

            JString(JPrimitiveCharArray* chars,jint off,jint length);

            JString(JPrimitiveByteArray* bytes);

            JString(JPrimitiveByteArray* bytes,jint off,jint length);

            JString(JPrimitiveByteArray* bytes, jint off, jint lenght, JString* charsetName);

            JString(jchar c);

            static jcpp::lang::JClass* getClazz();

            virtual jcpp::lang::JClass* getClass();

            virtual jint length();

            virtual jbool isEmpty();

            virtual jchar charAt(jint index);

            virtual jint codePointAt(jint index);

            virtual JString* reverse();

            virtual void getChars(jint srcBegin, jint srcEnd, JPrimitiveCharArray* dst, jint dstBegin);

            virtual JPrimitiveByteArray* getBytes();

            virtual jbool contentEquals(JCharSequence* cs);

            virtual jbool equalsIgnoreCase(JString* anotherString);

            virtual jbool startsWith(JString* prefix, jint toffset);

            virtual jbool startsWith(JString* prefix);

            virtual jbool endsWith(JString* prefix);

            virtual jint indexOf(jchar c);

            virtual jint indexOf(jchar c,jint fromIndex);

            virtual jint lastIndexOf(jchar c);

            virtual jint lastIndexOf(jchar c,jint fromIndex);

            virtual jint indexOf(JString* s);

            virtual jint indexOf(JString*,jint fromIndex);

            virtual jint lastIndexOf(JString* s);

            virtual jint lastIndexOf(JString*,jint fromIndex);

            virtual JString* replace(jchar oldchar,jchar newchar);

            virtual JString* substring(jint start);

            virtual JString* substring(jint start,jint end);

            virtual JCharSequence* subSequence(jint beginIndex, jint endIndex);

            virtual JString* concat(JString* str);

            virtual jbool contains(JCharSequence* s);

            virtual JString* toLowerCase();

            virtual JString* toUpperCase();

            virtual JString* trim();

            virtual JPrimitiveCharArray* toCharArray();

            virtual jint compareTo(JObject* o);

            virtual jint compareToIgnoreCase(JString* str);

            static jcpp::util::JComparator* CASE_INSENSITIVE_ORDER;

            virtual JString* clone();

            virtual jbool equals(JObject* other);

            virtual jint hashCode();

            virtual JString* toString();

            virtual JString* intern(JString* s);

            virtual ~JString();

            friend class JAbstractStringBuilder;
            friend class jcpp::net::JURLClassLoader;
            friend class JClassLoader;
            friend class JDouble;
            friend class JFloat;
            friend class JInteger;
            friend class JLong;
            friend class JPrimitiveCharArray;
            friend class JPrimitiveLongArray;
            friend class JPrimitiveFloatArray;
            friend class JPrimitiveShortArray;
            friend class JPrimitiveDoubleArray;
            friend class JPrimitiveBooleanArray;
            friend class JPrimitiveIntArray;
            friend class JPrimitiveByteArray;
            friend class JPrimitiveLongArray;
            friend class JPrimitiveObjectArray;
            friend class JThread;
            friend class JThrowable;
            friend class JProcessBuilder;
            friend class JProcess;
            friend class JSystem;
            friend class jcpp::io::JFileOutputStream;
            friend class jcpp::io::JFileInputStream;
            friend class jcpp::io::JFile;
            friend class jcpp::util::JHashMap;
            friend class jcpp::net::JInetAddress;
        };
    }
}
#endif
