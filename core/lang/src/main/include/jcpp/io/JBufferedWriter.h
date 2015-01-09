#ifndef JCPP_IO_JBUFFEREDWRITER_H
#define JCPP_IO_JBUFFEREDWRITER_H

#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
    	class JPrintStream;

        //@Class(canonicalName="java.io.BufferedWriter", simpleName="BufferedWriter");
        class JCPP_EXPORT JBufferedWriter : public JWriter  {
            protected:
                JWriter* out;
                JPrimitiveCharArray* cb;
                jint nChars;
                jint nextChar;
                void ensureOpen();
                void flushBuffer();
                friend class JPrintStream;

            public:
                JBufferedWriter(JWriter* out,jint size=8192);

                static jcpp::lang::JClass* getClazz();

                virtual void write(jint c);

                virtual void write(JPrimitiveCharArray* c);

                virtual void write(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual void write(JString* str);

                virtual void write(JString* str, jint off, jint len);

                virtual void newLine();

                virtual void flush();

                virtual void close();

                virtual ~JBufferedWriter();
        };
    }
}

#endif
