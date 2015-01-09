#ifndef JCPP_IO_JPUSHBACKREADER_H
#define JCPP_IO_JPUSHBACKREADER_H

#include "jcpp/io/JFilterReader.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.PushbackReader", simpleName="PushbackReader");
        class JCPP_EXPORT JPushbackReader : public JFilterReader  {
            protected:
                JPrimitiveCharArray* buf;
                jint pos;
                void ensureOpen();

            public:
                static jcpp::lang::JClass* getClazz();

                JPushbackReader(JReader* in,jint size=1);

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual void unread(jint c);

                virtual void unread(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual void unread(JPrimitiveCharArray* cbuf);

                virtual jbool ready();

                virtual void mark(jint m);

                virtual void reset();

                virtual jbool markSupported();

                virtual void close();

                virtual jlong skip(jlong n);

                virtual ~JPushbackReader();
        };
    }
}

#endif
