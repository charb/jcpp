#ifndef JCPP_IO_JSTRINGWRITER_H
#define JCPP_IO_JSTRINGWRITER_H

#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.StringWriter", simpleName="StringWriter");
        class JCPP_EXPORT JStringWriter : public JWriter  {
            protected:
                JStringBuffer* buf;

            public:
                static jcpp::lang::JClass* getClazz();

                JStringWriter();

                virtual void write(jint c);

                virtual void write(JPrimitiveCharArray* buf,jint off,jint len);

                virtual void write(JString* str);

                virtual void write(JString* str,jint off,jint len);

                virtual JStringWriter* append(JCharSequence* csq);

                virtual JStringWriter* append(JCharSequence* csq,jint start,jint end);

                virtual JStringWriter* append(jchar c);

                virtual JString* toString();

                virtual JStringBuffer* getBuffer();

                virtual void flush();

                virtual void close();

                virtual ~JStringWriter();
        };
    }
}

#endif
