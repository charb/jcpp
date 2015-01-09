#ifndef JCPP_IO_JFILEOUTPUTSTREAM_H
#define JCPP_IO_JFILEOUTPUTSTREAM_H

#include "jcpp/io/JOutputStream.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/native/api/io/NativeFileOutputStream.h"

using namespace jcpp::lang;
using jcpp::native::api::io::NativeFileOutputStream;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FileOutputStream", simpleName="FileOutputStream");
        class JCPP_EXPORT JFileOutputStream : public JOutputStream  {
            protected:
                JObject* closeLock;
                jbool bIsClosed;
                NativeFileOutputStream* nativeStream;
                
            public:
                JFileOutputStream(JString* name,jbool append=false);

                JFileOutputStream(JFile* file,jbool append=false);

                static jcpp::lang::JClass* getClazz();

                virtual void write(jint b);

                virtual void write(JPrimitiveByteArray* b);

                virtual void write(JPrimitiveByteArray* b,jint off,jint len);

                virtual void close();

                virtual void finalize();

                virtual ~JFileOutputStream();
        };
    }
}

#endif
