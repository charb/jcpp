#ifndef JCPP_IO_JPIPEDWRITER_H
#define JCPP_IO_JPIPEDWRITER_H

#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JPipedReader;

        //@Class(canonicalName="java.io.PipedWriter", simpleName="PipedWriter");
        class JCPP_EXPORT JPipedWriter : public JWriter  {
            protected:
                JPipedReader* sink;
                jbool closed;

            public:
                static jcpp::lang::JClass* getClazz();

                JPipedWriter(JPipedReader* snk);

                JPipedWriter();

                virtual void connect(JPipedReader* snk);

                virtual void write(jint c);

                virtual void write(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual void flush();

                virtual void close();

                virtual ~JPipedWriter();
        };
    }
}

#endif
