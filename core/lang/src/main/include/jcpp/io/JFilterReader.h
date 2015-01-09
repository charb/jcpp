#ifndef JCPP_IO_JFILTERREADER_H
#define JCPP_IO_JFILTERREADER_H

#include "jcpp/io/JReader.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FilterReader", simpleName="FilterReader");
        class JCPP_EXPORT JFilterReader : public JReader  {
            protected:
                JReader* in;
                JFilterReader(jcpp::lang::JClass* _class,JReader* in);

            public:
                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual jlong skip(jlong n);

                virtual jbool ready();

                virtual jbool markSupported();

                virtual void mark(jint m);

                virtual void reset();

                virtual void close();

                virtual ~JFilterReader();
        };
    }
}

#endif
