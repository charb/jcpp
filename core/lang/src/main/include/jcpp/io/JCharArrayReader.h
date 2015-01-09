#ifndef JCPP_IO_JCHARARRAYREADER_H
#define JCPP_IO_JCHARARRAYREADER_H

#include "jcpp/io/JReader.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.CharArrayReader", simpleName="CharArrayReader");
        class JCPP_EXPORT JCharArrayReader : public JReader  {
            protected:
                JPrimitiveCharArray* buf;
                jint pos;
                jint markedPos;
                jint count;
                void ensureOpen();

            public:
                JCharArrayReader(JPrimitiveCharArray* buf);

                JCharArrayReader(JPrimitiveCharArray* buf,jint pos,jint length);

                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* b, jint off, jint len);

                virtual jlong skip(jlong n);

                virtual jbool ready();

                virtual jbool markSupported();

                virtual void mark(jint m);

                virtual void reset();

                virtual void close();

                virtual ~JCharArrayReader();
        };
    }
}

#endif
