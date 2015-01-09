#ifndef JCPP_IO_JPRINT_WRITER_H
#define JCPP_IO_JPRINT_WRITER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/io/JBufferedWriter.h"
#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/JCharSequence.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.PrintWriter", simpleName="PrintWriter");
        class JCPP_EXPORT JPrintWriter : public JWriter{
        protected:
            JWriter* out;
            jbool autoFlush;
            jbool trouble;
            JPrintStream* psOut;
            virtual void ensureOpen();
            virtual void setError();
            virtual void clearError();
            virtual void newLine();
            
        public:
            JPrintWriter(JWriter* out,jbool autoFlush=false);

            JPrintWriter(JOutputStream* out,jbool autoFlush=false);

            JPrintWriter(JString* fileName,jbool autoFlush=false);

            JPrintWriter(JFile* file,jbool autoFlush=false);
            
            static jcpp::lang::JClass* getClazz();

            virtual void flush();

            virtual void close();

            virtual jbool checkError();

            virtual void write(jint c);

            virtual void write(JPrimitiveCharArray* b, jint off, jint len);

            virtual void write(JPrimitiveCharArray* b);

            virtual void write(JString* b, jint off, jint len);

            virtual void write(JString* b);

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

            virtual JPrintWriter* append(JCharSequence* seq);

            virtual JPrintWriter* append(JCharSequence* seq,jint start,jint end);
            
            virtual JPrintWriter* append(jchar c);

            virtual ~JPrintWriter();
        };
    }
}

#endif
