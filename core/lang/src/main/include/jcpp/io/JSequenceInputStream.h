#ifndef JCPP_IO_JSEQUENCEINPUTSTREAM_H
#define JCPP_IO_JSEQUENCEINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/util/JEnumeration.h"
#include "jcpp/util/JVector.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.SequenceInputStream", simpleName="SequenceInputStream");
        class JCPP_EXPORT JSequenceInputStream : public JInputStream  {
            protected:
                JVector* vec;
                JEnumeration* e;
                JInputStream* in;
                void nextStream();

            public:
                static jcpp::lang::JClass* getClazz();

                JSequenceInputStream(JEnumeration* e);

                JSequenceInputStream(JInputStream* s1,JInputStream* s2);

                virtual void close();

                virtual jint read(JPrimitiveByteArray* b, jint offset, jint len);

                virtual jint read();

                virtual jint available();

                virtual ~JSequenceInputStream();
        };
    }
}

#endif
