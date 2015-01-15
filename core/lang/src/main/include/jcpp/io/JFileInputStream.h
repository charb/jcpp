#ifndef JCPP_IO_JFILEINPUTSTREAM_H
#define JCPP_IO_JFILEINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/native/api/io/NativeFileInputStream.h"

using namespace jcpp::lang;
using jcpp::native::api::io::NativeFileInputStream;

//TODO implement JFileDescriptor
namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FileInputStream", simpleName="FileInputStream");
        class JCPP_EXPORT JFileInputStream : public JInputStream  {
            protected:
        		// @IgnoreReflection()
        		NativeFileInputStream * nativeStream;

                JObject* closeLock;
                jbool bIsClosed;

            public:
                JFileInputStream(JString* name);

                JFileInputStream(JFile* file);

                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveByteArray* b);

                virtual jint read(JPrimitiveByteArray* b,jint off,jint len);

                virtual jlong skip(jlong n);

                virtual jint available();

                virtual void close();

                virtual void finalize();

                virtual ~JFileInputStream();
        };
    }
}

#endif
