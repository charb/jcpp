#ifndef JCPP_LANG_JABSTRACTSTRINGBUILDER_H
#define JCPP_LANG_JABSTRACTSTRINGBUILDER_H

#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveInt.h"

namespace jcpp{
    namespace lang{
        class JStringBuffer;

        // @Class(canonicalName="java.lang.AbstractStringBuilder", simpleName="AbstractStringBuilder");
        class JCPP_EXPORT JAbstractStringBuilder : public JObject, public JAppendable, public JCharSequence  {
        	private:
        		void ensureCapacityInternal(jint c);

        		// @IgnoreReflection()
        		void append(const std::string& str);
        		// @IgnoreReflection()
        		void insert(jint offset, const std::string& str);
            protected:
        		JPrimitiveCharArray * value;
        		JPrimitiveInt* count;

                JAbstractStringBuilder(jcpp::lang::JClass* _class);
            public:
                static jcpp::lang::JClass* getClazz();

                virtual jint length();

                virtual jint capacity();

                virtual void ensureCapacity(jint c);

                virtual void trimToSize();

                virtual void setLength(jint l);

                virtual jchar charAt(jint index);

                virtual void getChars(jint srcBegin,jint srcEnd,JPrimitiveCharArray* dst,jint dstBegin);

                virtual void setCharAt(jint index,jchar c);

                virtual JAbstractStringBuilder* append(JObject* o);

                virtual JAbstractStringBuilder* append(JString* o);

                virtual JAbstractStringBuilder* append(JStringBuffer* sb);

                virtual JAbstractStringBuilder* append(JCharSequence* s);

                virtual JAbstractStringBuilder* append(JCharSequence* s,jint start,jint end);

                virtual JAbstractStringBuilder* append(JPrimitiveCharArray* str,jint offset,jint length);

                virtual JAbstractStringBuilder* append(JString* str,jint offset,jint length);

                // @IgnoreReflection()
                virtual JAbstractStringBuilder* append(const char * str);

                // @IgnoreReflection()
                virtual JAbstractStringBuilder* append(const wchar_t* wstr);

                virtual JAbstractStringBuilder* append(jbool b);

                virtual JAbstractStringBuilder* append(jchar c);

                virtual JAbstractStringBuilder* append(jint i);

                virtual JAbstractStringBuilder* append(jlong l);

                virtual JAbstractStringBuilder* append(jfloat f);

                virtual JAbstractStringBuilder* append(jdouble d);

                virtual JAbstractStringBuilder* deleteChar(jint start,jint end);

                virtual JAbstractStringBuilder* deleteCharAt(jint index);

                virtual JAbstractStringBuilder* replace(jint start,jint end,JString* str);

                virtual JString* substring(jint start);

                virtual JCharSequence* subSequence(jint start,jint end);

                virtual JString* substring(jint start,jint end);

                virtual JAbstractStringBuilder* insert(jint index,JPrimitiveCharArray* str,jint offset,jint len);

                virtual JAbstractStringBuilder* insert(jint offset,JObject* o);

                virtual JAbstractStringBuilder* insert(jint offset,JString* str);

                virtual JAbstractStringBuilder* insert(jint offset,JCharSequence* s);

                virtual JAbstractStringBuilder* insert(jint offset,JCharSequence* s,jint start,jint end);

                // @IgnoreReflection()
                virtual JAbstractStringBuilder* insert(jint offset,const char * str);

                // @IgnoreReflection()
                virtual JAbstractStringBuilder* insert(jint offset,const wchar_t* wstr);

                virtual JAbstractStringBuilder* insert(jint offset,jbool b);

                virtual JAbstractStringBuilder* insert(jint offset,jchar c);

                virtual JAbstractStringBuilder* insert(jint offset,jint i);

                virtual JAbstractStringBuilder* insert(jint offset,jlong l);

                virtual JAbstractStringBuilder* insert(jint offset,jfloat f);

                virtual JAbstractStringBuilder* insert(jint offset,jdouble d);

                virtual jint indexOf(JString* str);

                virtual jint indexOf(JString* str,jint fromIndex);

                virtual jint lastIndexOf(JString* str);

                virtual jint lastIndexOf(JString* str,jint fromIndex);

                virtual JAbstractStringBuilder* reverse();

                virtual JString* toString();

                virtual jbool equals(JObject *o);

                virtual ~JAbstractStringBuilder();
        };
    }
}

#endif
