#ifndef JCPP_IO_JINPUTSTREAM_H
#define JCPP_IO_JINPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/io/JCloseable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.InputStream", simpleName="InputStream");
        class JCPP_EXPORT JInputStream : public JObject, public JCloseable{
        protected:
            static const jint SKIP_BUFFER_SIZE = 2048;
            JPrimitiveByteArray* skipBuffer;
            JInputStream(jcpp::lang::JClass* _class);

        public:
            JInputStream();

            static jcpp::lang::JClass* getClazz();

            virtual jint available();

            virtual jint read()=0;

            virtual jint read(JPrimitiveByteArray* b);

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual jlong skip(jlong n);

            virtual void mark(jint readlimit);

            virtual void reset();

            virtual jbool markSupported();

            virtual void close();

            virtual ~JInputStream();
        };
    }
}

#endif
