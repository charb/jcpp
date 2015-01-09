#ifndef JCPP_IO_JPRINT_STREAM_H
#define JCPP_IO_JPRINT_STREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFilterOutputStream.h"
#include "jcpp/io/JCloseable.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/io/JBufferedWriter.h"
#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/JCharSequence.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.PrintStream", simpleName="PrintStream");
        class JCPP_EXPORT JPrintStream : public JFilterOutputStream, public JAppendable{
        protected:
            jbool autoFlush;
            jbool trouble;
            JBufferedWriter* textOut;
            JOutputStreamWriter* charOut;
            jbool closing;
            virtual void ensureOpen();
            virtual void setError();
            virtual void clearError();
            virtual void write(JPrimitiveCharArray* b);
            virtual void write(JString* str);
            virtual void newLine();

        public:
            JPrintStream(JOutputStream* out, JString *encoding, jbool autoFlush=false);

            JPrintStream(JString* fileName, JString *encoding, jbool autoFlush=false);

            JPrintStream(JFile* file, JString *encoding, jbool autoFlush=false);

            JPrintStream(JFile* file,jbool autoFlush, JString* encoding);

            static jcpp::lang::JClass* getClazz();

            virtual void flush();

            virtual void close();

            virtual jbool checkError();

            virtual void write(jint b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void print(jbool b);

            virtual void print(jchar c);

            virtual void print(jint i);

            virtual void print(jlong l);

            virtual void print(jfloat f);

            virtual void print(jdouble d);

            virtual void print(JPrimitiveCharArray* s);

            virtual void print(JString* s);

            virtual void print(JObject* s);

            virtual void println();

            virtual void println(jbool b);

            virtual void println(jchar c);

            virtual void println(jint i);

            virtual void println(jlong l);

            virtual void println(jfloat f);

            virtual void println(jdouble d);

            virtual void println(JPrimitiveCharArray* a);

            virtual void println(JString* s);

            virtual void println(JObject* o);

            virtual JPrintStream* append(JCharSequence* seq);

            virtual JPrintStream* append(JCharSequence* seq,jint start,jint end);

            virtual JPrintStream* append(jchar c);

            virtual ~JPrintStream();
        };
    }
}

#endif
