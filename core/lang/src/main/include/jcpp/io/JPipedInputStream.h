#ifndef JCPP_IO_JPIPEDINPUTSTREAM_H
#define JCPP_IO_JPIPEDINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JPipedOutputStream;

        //@Class(canonicalName="java.io.PipedInputStream", simpleName="PipedInputStream");
        class JCPP_EXPORT JPipedInputStream : public JInputStream  {
            protected:
                jbool closedByWriter;
                jbool closedByReader;
                jbool connected;
                JPrimitiveByteArray* buffer;
                jint in;
                jint out;
                void initPipe(jint pipeSize);
                void receive(jint b);
                void receive(JPrimitiveByteArray* b,jint off,jint len);
                void checkStateForReceive();
                void awaitSpace();
                void receivedLast();
                friend class JPipedOutputStream;

            public:
                static jcpp::lang::JClass* getClazz();

                JPipedInputStream(JPipedOutputStream* src,jint pipeSize=2014);

                JPipedInputStream(jint pipeSize=2014);

                virtual void connect(JPipedOutputStream* src);

                virtual jint read();

                virtual jint read(JPrimitiveByteArray* b,jint off,jint len);

                virtual jint available();

                virtual void close();

                virtual ~JPipedInputStream();
        };
    }
}

#endif // JPIPEDINPUTSTREAM_H
