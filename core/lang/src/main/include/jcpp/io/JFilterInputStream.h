#ifndef JCPP_IO_JFILTERINPUTSTREAM_H
#define JCPP_IO_JFILTERINPUTSTREAM_H

#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FilterInputStream", simpleName="FilterInputStream");
        class JCPP_EXPORT JFilterInputStream : public JInputStream{
        protected:
            JInputStream* in;
            JFilterInputStream(JInputStream* in,jcpp::lang::JClass* _class);

        public:
            static jcpp::lang::JClass* getClazz();

            virtual jint available();

            virtual jint read();

            virtual jint read(JPrimitiveByteArray* b);

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual jlong skip(jlong n);

            virtual void mark(jint readlimit);

            virtual void reset();

            virtual jbool markSupported();
            
            virtual void close();
            
            virtual ~JFilterInputStream();
        };
    }
}


#endif
