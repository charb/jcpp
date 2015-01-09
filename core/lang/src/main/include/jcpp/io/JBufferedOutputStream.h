#ifndef JCPP_IO_JBUFFEREDOUTPUTSTREAM_H
#define JCPP_IO_JBUFFEREDOUTPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFilterOutputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.BufferedOutputStream", simpleName="BufferedOutputStream");
        class JCPP_EXPORT JBufferedOutputStream : public JFilterOutputStream{
        protected:
            JPrimitiveByteArray* buf;
            jint count;
            void flushBuffer();

        public:
            JBufferedOutputStream(JOutputStream* out, jint size=8192);

            static jcpp::lang::JClass* getClazz();

            virtual void write(jint b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void flush();

            virtual ~JBufferedOutputStream();
        };
    }
}

#endif
