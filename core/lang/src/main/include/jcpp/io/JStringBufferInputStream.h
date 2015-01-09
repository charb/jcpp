#ifndef JCPP_IO_JSTRINGBUFFERINPUTSTREAM_H
#define JCPP_IO_JSTRINGBUFFERINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.StringBufferInputStream", simpleName="StringBufferInputStream");
        class JCPP_EXPORT JStringBufferInputStream : public JInputStream  {

            protected:
                JString* buffer;
                jint pos;
                jint count;

            public:
                JStringBufferInputStream(JString* s);

                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveByteArray* b, jint offset, jint len);

                virtual jlong skip(jlong n);

                virtual jint available();

                virtual void reset();

                virtual ~JStringBufferInputStream();
        };
    }
}

#endif
