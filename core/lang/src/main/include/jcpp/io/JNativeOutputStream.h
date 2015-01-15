#ifndef JCPP_IO_JNATIVEOUTPUTSTREAM_H
#define JCPP_IO_JNATIVEOUTPUTSTREAM_H

#include "jcpp/io/JOutputStream.h"
#include "jcpp/native/api/io/NativeOutputStream.h"

using namespace jcpp::lang;
using jcpp::native::api::io::NativeOutputStream;

namespace jcpp{
    namespace io{
    	//@Class(canonicalName="java.io.NativeOutputStream", simpleName="NativeOutputStream");
        class JCPP_EXPORT JNativeOutputStream : public JOutputStream  {
            protected:
        		// @IgnoreReflection()
        		NativeOutputStream* stream;

        		jbool deleteNativeStreamAtFinalize;

            public:
        		// @IgnoreReflection()
        		JNativeOutputStream(NativeOutputStream* stream, jbool deleteNativeStreamAtFinalize);

                static jcpp::lang::JClass* getClazz();

                virtual void write(jint b);

                virtual void write(JPrimitiveByteArray* b);

                virtual void write(JPrimitiveByteArray* b, jint off, jint len);

                virtual void flush();

                virtual void close();

                virtual void finalize();

                virtual ~JNativeOutputStream();
        };
    }
}

#endif // JCPP_IO_JNATIVEOUTPUTSTREAM_H
