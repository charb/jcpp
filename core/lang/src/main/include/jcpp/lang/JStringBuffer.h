#ifndef JCPP_LANG_JSTRINGBUFFER_H
#define JCPP_LANG_JSTRINGBUFFER_H

#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JAbstractStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::io;

namespace jcpp{
    namespace io{
        class JObjectOutputStream;
        class JObjectInputStream;
    }
    namespace lang{
    	class JStringBufferClass;

        class JCPP_EXPORT JStringBuffer : public JAbstractStringBuilder  , public JSerializable{
            protected:
                static JPrimitiveObjectArray* serialPersistentFields;
                static JPrimitiveObjectArray* getSerialPersistentFields();
                virtual void writeObject(JObjectOutputStream* s);
                virtual void readObject(JObjectInputStream* s);
                friend class JStringBufferClass;

            public:
                static jcpp::lang::JClass* getClazz();

                JStringBuffer();

                JStringBuffer(JString* str);

                JStringBuffer(JCharSequence* cs);

                virtual jint length();

                virtual jint capacity();

                virtual void ensureCapacity(jint c);

                virtual void trimToSize();

                virtual void setLength(jint l);

                virtual jchar charAt(jint index);

                virtual void getChars(jint srcBegin,jint srcEnd,JPrimitiveCharArray* dst,jint dstBegin);

                virtual void setCharAt(jint index,jchar c);

                virtual JStringBuffer* append(JObject* o);

                virtual JStringBuffer* append(JString* o);

                virtual JStringBuffer* append(JStringBuffer* sb);

                virtual JStringBuffer* append(JCharSequence* s);

                virtual JStringBuffer* append(JCharSequence* s,jint start,jint end);

                virtual JStringBuffer* append(JPrimitiveCharArray* str,jint offset,jint length);

                virtual JStringBuffer* append(JString* str,jint offset,jint length);

                virtual JStringBuffer* append(const char * str);

                virtual JStringBuffer* append(const wchar_t* wstr);

                virtual JStringBuffer* append(jbool b);

                virtual JStringBuffer* append(jchar c);

                virtual JStringBuffer* append(jint i);

                virtual JStringBuffer* append(jlong l);

                virtual JStringBuffer* append(jfloat f);

                virtual JStringBuffer* append(jdouble d);

                virtual JStringBuffer* deleteChar(jint start,jint end);

                virtual JStringBuffer* deleteCharAt(jint index);

                virtual JStringBuffer* replace(jint start,jint end,JString* str);

                virtual JString* substring(jint start);

                virtual JCharSequence* subSequence(jint start,jint end);

                virtual JString* substring(jint start,jint end);

                virtual JStringBuffer* insert(jint index,JPrimitiveCharArray* str,jint offset,jint len);

                virtual JStringBuffer* insert(jint offset,JObject* o);

                virtual JStringBuffer* insert(jint offset,JString* str);

                virtual JStringBuffer* insert(jint offset,JCharSequence* s);

                virtual JStringBuffer* insert(jint offset,JCharSequence* s,jint start,jint end);

                virtual JStringBuffer* insert(jint offset,const char * str);

                virtual JStringBuffer* insert(jint offset,const wchar_t* wstr);

                virtual JStringBuffer* insert(jint offset,jbool b);

                virtual JStringBuffer* insert(jint offset,jchar c);

                virtual JStringBuffer* insert(jint offset,jint i);

                virtual JStringBuffer* insert(jint offset,jlong l);

                virtual JStringBuffer* insert(jint offset,jfloat f);

                virtual JStringBuffer* insert(jint offset,jdouble d);

                virtual jint indexOf(JString* str);

                virtual jint indexOf(JString* str,jint fromIndex);

                virtual jint lastIndexOf(JString* str);

                virtual jint lastIndexOf(JString* str,jint fromIndex);

                virtual JStringBuffer* reverse();

                virtual JString* toString();

                virtual ~JStringBuffer();
        };
    }
}

#endif
