#ifndef JCPP_IO_JBUFFEREDINPUTSTREAM_H
#define JCPP_IO_JBUFFEREDINPUTSTREAM_H

#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFilterInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.BufferedInputStream", simpleName="BufferedInputStream");
        class JCPP_EXPORT JBufferedInputStream : public JFilterInputStream{
        protected:
            JPrimitiveByteArray* buf;
            jint count;
            jint pos;
            jint markpos;
            jint marklimit;
            JInputStream* getInIfOpen();
            JPrimitiveByteArray* getBufIfOpen();
            void fill();
            jint read1(JPrimitiveByteArray* b, jint off, jint len);

        public:
            JBufferedInputStream(JInputStream* in, jint size=8192);

            static jcpp::lang::JClass* getClazz();

            virtual jint read();

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual jlong skip(jlong n);

            virtual jint available();

            virtual void mark(jint readlimit);

            virtual void reset();

            virtual jbool markSupported();

            virtual void close();

            virtual ~JBufferedInputStream();
        };
    }
}

#endif
