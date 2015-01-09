#ifndef JCPP_IO_JPUSHBACKINPUTSTREAM_H
#define JCPP_IO_JPUSHBACKINPUTSTREAM_H

#include "jcpp/io/JFilterInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.PushbackInputStream", simpleName="PushbackInputStream");
        class JCPP_EXPORT JPushbackInputStream : public JFilterInputStream  {
            protected:
                JPrimitiveByteArray* buf;
                jint pos;
                void ensureOpen();

            public:
                static jcpp::lang::JClass* getClazz();

                JPushbackInputStream(JInputStream* in,jint size=1);

                virtual jint read();

                virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

                virtual void unread(jint b);

                virtual void unread(JPrimitiveByteArray* b,jint off,jint len);

                virtual void unread(JPrimitiveByteArray* b);

                virtual jint available();

                virtual jlong skip(jlong n);

                virtual jbool markSupported();

                virtual void mark(jint r);

                virtual void reset();

                virtual void close();

                virtual ~JPushbackInputStream();
        };
    }
}

#endif
