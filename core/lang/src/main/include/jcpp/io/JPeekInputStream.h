#ifndef JCPP_IO_JPEEKINPUTSTREAM_H
#define JCPP_IO_JPEEKINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectInputStream$PeekInputStream", simpleName="ObjectInputStream$PeekInputStream");
        class JCPP_EXPORT JPeekInputStream : public JInputStream {
        protected:
            JInputStream* in;
            jint peekb;

        public:
            JPeekInputStream(JInputStream *in);

            static jcpp::lang::JClass* getClazz();

            virtual jint peek();

            virtual jint read();

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual void readFully(JPrimitiveByteArray* b, jint off, jint len);

            virtual jlong skip(jlong len);

            virtual jint available();

            virtual void close();
            
            virtual ~JPeekInputStream();
        };
    }
}

#endif
