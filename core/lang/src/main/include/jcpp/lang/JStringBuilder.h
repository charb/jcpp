#ifndef JCPP_LANG_JSTRINGBUILDER_H
#define JCPP_LANG_JSTRINGBUILDER_H

#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JAbstractStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::io;

namespace jcpp{
    namespace io{
        class JObjectInputStream;
        class JObjectOutputStream;
    }
    namespace lang{

    	// @Class(canonicalName="java.lang.StringBuilder", simpleName="StringBuilder");
        class JCPP_EXPORT JStringBuilder : public JAbstractStringBuilder  , public JSerializable{
        	private:
        		static const jlong serialVersionUID = 4383685877147921099LL;

            protected:
                virtual void writeObject(jcpp::io::JObjectOutputStream* out);
                virtual void readObject(jcpp::io::JObjectInputStream* in);

            public:
                static jcpp::lang::JClass* getClazz();

                JStringBuilder();

                JStringBuilder(JString* str);

                JStringBuilder(JCharSequence* seq);

                virtual JStringBuilder* append(JObject* o);

                virtual JStringBuilder* append(JString* o);

                virtual JStringBuilder* append(JStringBuffer* sb);

                virtual JStringBuilder* append(JCharSequence* sq);

                virtual JStringBuilder* append(JCharSequence* sq,jint start,jint end);

                virtual JStringBuilder* append(JPrimitiveCharArray* str,jint offset,jint len);

                virtual JStringBuilder* append(JString* str,jint offset,jint len);

                // @IgnoreReflection()
                virtual JStringBuilder* append(const char * str);

                // @IgnoreReflection()
                virtual JStringBuilder* append(const wchar_t* wstr);

                virtual JStringBuilder* append(jbool b);

                virtual JStringBuilder* append(jchar c);

                virtual JStringBuilder* append(jint i);

                virtual JStringBuilder* append(jlong l);

                virtual JStringBuilder* append(jfloat f);

                virtual JStringBuilder* append(jdouble d);

                virtual JStringBuilder* deleteChar(jint start,jint end);

                virtual JStringBuilder* deleteCharAt(jint index);

                virtual JStringBuilder* replace(jint start,jint end,JString* str);

                virtual JStringBuilder* insert(jint index,JPrimitiveCharArray* str,jint offset,jint len);

                virtual JStringBuilder* insert(jint offset,JObject* o);

                virtual JStringBuilder* insert(jint offset,JString* str);

                virtual JStringBuilder* insert(jint offset,JCharSequence* s);

                virtual JStringBuilder* insert(jint offset,JCharSequence* s,jint start,jint end);

                // @IgnoreReflection()
                virtual JStringBuilder* insert(jint offset,const char * str);

                // @IgnoreReflection()
                virtual JStringBuilder* insert(jint offset,const wchar_t* wstr);

                virtual JStringBuilder* insert(jint offset,jbool b);

                virtual JStringBuilder* insert(jint offset,jchar c);

                virtual JStringBuilder* insert(jint offset,jint i);

                virtual JStringBuilder* insert(jint offset,jlong l);

                virtual JStringBuilder* insert(jint offset,jfloat f);

                virtual JStringBuilder* insert(jint offset,jdouble d);

                virtual JStringBuilder* reverse();

                virtual ~JStringBuilder();
        };
    }
}

#endif
