#ifndef JCPP_IO_JBYTEARRAYOUTPUTSTREAM_H
#define JCPP_IO_JBYTEARRAYOUTPUTSTREAM_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ByteArrayOutputStream", simpleName="ByteArrayOutputStream");
        class JCPP_EXPORT JByteArrayOutputStream : public JOutputStream  {
            protected:
                JPrimitiveByteArray* buf;
                jint count;
                void ensureCapacity(jint minCapacity);
                void grow(jint minCapacity);

            public:
                JByteArrayOutputStream(jint size=32);

                static jcpp::lang::JClass* getClazz();

                virtual void write(jint b);

                virtual void write(JPrimitiveByteArray* b, jint off, jint l);

                virtual void writeTo(JOutputStream* out);

                virtual void reset();

                virtual JPrimitiveByteArray* toByteArray();

                virtual jint size();

                virtual JString* toString();

                virtual void close();

                virtual ~JByteArrayOutputStream();
        };
    }
}

#endif
