#ifndef JCPP_IO_JPIPEDREADER_H
#define JCPP_IO_JPIPEDREADER_H

#include "jcpp/io/JReader.h"
#include "jcpp/io/JPipedWriter.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.PipedReader", simpleName="PipedReader");
        class JCPP_EXPORT JPipedReader : public JReader  {
            protected:
                jbool closedByWriter;
                jbool closedByReader;
                jbool connected;
                JPrimitiveCharArray* buffer;
                jint in;
                jint out;
                void initPipe(jint pipeSize);
                void receive(jint c);
                void receive(JPrimitiveCharArray* c,jint off,jint len);
                void receivedLast();
                friend class JPipedWriter;

            public:
                JPipedReader(JPipedWriter* src, jint pipeSize=1024);

                JPipedReader(jint pipeSize=1024);

                static jcpp::lang::JClass* getClazz();

                virtual void connect(JPipedWriter* src);

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual jbool ready();

                virtual void close();

                virtual ~JPipedReader();
        };
    }
}

#endif
