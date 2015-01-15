#ifndef JCPP_IO_JNATIVEINPUTSTREAM_H
#define JCPP_IO_JNATIVEINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/native/api/io/NativeInputStream.h"

using namespace jcpp::lang;
using jcpp::native::api::io::NativeInputStream;

namespace jcpp{
    namespace io{
    	//@Class(canonicalName="java.io.NativeInputStream", simpleName="NativeInputStream");
        class JCPP_EXPORT JNativeInputStream : public JInputStream  {
            protected:
        		// @IgnoreReflection()
        		NativeInputStream* stream;

        		jbool deleteNativeStreamAtFinalize;

            public:
        		// @IgnoreReflection()
        		JNativeInputStream(NativeInputStream* stream, jbool deleteNativeStreamAtFinalize);

                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveByteArray* b, jint off, jint l);

                virtual jlong skip(jlong l);

                virtual jint available();

                virtual void close();

                virtual void finalize();

                virtual ~JNativeInputStream();
        };
    }
}

#endif // JCPP_IO_JNATIVEINPUTSTREAM_H
