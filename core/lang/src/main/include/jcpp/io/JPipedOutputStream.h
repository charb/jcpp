#ifndef JCPP_IO_JPIPEDOUTPUTSTREAM_H
#define JCPP_IO_JPIPEDOUTPUTSTREAM_H

#include "jcpp/io/JOutputStream.h"
#include "jcpp/io/JPipedInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.PipedOutputStream", simpleName="PipedOutputStream");
        class JCPP_EXPORT JPipedOutputStream : public JOutputStream  {
            protected:
                JPipedInputStream* sink;

            public:
                static jcpp::lang::JClass* getClazz();

                JPipedOutputStream(JPipedInputStream* sink);

                JPipedOutputStream();

                virtual void connect(JPipedInputStream* sink);

                virtual void write(jint b);

                virtual void write(JPrimitiveByteArray* b, jint off, jint len);

                virtual void flush();

                virtual void close();

                virtual ~JPipedOutputStream();
        };
    }
}

#endif
