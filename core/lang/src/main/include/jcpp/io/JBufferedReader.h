#ifndef JCPP_IO_JBUFFEREDREADER_H
#define JCPP_IO_JBUFFEREDREADER_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JReader.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.BufferedReader", simpleName="BufferedReader");
        class JCPP_EXPORT JBufferedReader : public JReader  {
            protected:
                JReader* in;
                JPrimitiveCharArray* cb;
                jint nChars;
                jint nextChar;
                jint markedChar;
                jint readAheadLimit;
                jbool skipLF;
                jbool markedSkipLF;
                void ensureOpen();
                void fill();
                jint read1(JPrimitiveCharArray* cbuf, jint off,jint len);
                JString* readLine(jbool ignoreLF);
                JBufferedReader(jcpp::lang::JClass* _class,JReader* in,jint sz=8192);

            public:
                JBufferedReader(JReader* in,jint sz=8192);

                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* cbuf, jint off,jint len);

                virtual JString* readLine();

                virtual jlong skip(jlong n);

                virtual jbool ready();

                virtual jbool markSupported();

                virtual void mark(jint m);

                virtual void reset();

                virtual void close();

                virtual ~JBufferedReader();
        };
    }
}

#endif
