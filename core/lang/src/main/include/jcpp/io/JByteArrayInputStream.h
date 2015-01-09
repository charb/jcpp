#ifndef JCPP_IO_JBYTEARRAYINPUTSTREAM_H
#define JCPP_IO_JBYTEARRAYINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.ByteArrayInputStream", simpleName="ByteArrayInputStream");
        class JCPP_EXPORT JByteArrayInputStream : public JInputStream  {
            protected:
                JPrimitiveByteArray* buf;
                jint pos;
                jint imark;
                jint count;

            public:
                JByteArrayInputStream(JPrimitiveByteArray* buf);

                JByteArrayInputStream(JPrimitiveByteArray* buf,jint offset,jint l);

                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveByteArray* b, jint off, jint l);

                virtual jlong skip(jlong l);

                virtual jint available();

                virtual jbool markSupported();
                
                virtual void mark(jint m);

                virtual void reset();

                virtual void close();
                
                virtual ~JByteArrayInputStream();
        };
    }
}

#endif // JBYTEARRAYINPUTSTREAM_H
