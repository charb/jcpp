#ifndef JCPP_IO_JCHARARRAYWRITER_H
#define JCPP_IO_JCHARARRAYWRITER_H

#include "jcpp/lang/JString.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
    	//@Class(canonicalName="java.io.CharArrayWriter", simpleName="CharArrayWriter");
        class JCPP_EXPORT JCharArrayWriter : public JWriter  {
            protected:
                JPrimitiveCharArray* buf;
                jint count;


            public:
                JCharArrayWriter(jint size=32);
                
                static jcpp::lang::JClass* getClazz();

                virtual void write(jint c);

                virtual void write(JPrimitiveCharArray* c, jint offset, jint len);

                virtual void write(JString* str, jint offset, jint len);

                virtual void writeTo(JWriter* out);

                virtual JCharArrayWriter* append(JCharSequence* csq);

                virtual JCharArrayWriter* append(JCharSequence* csq,jint offset,jint len);

                virtual JCharArrayWriter* append(jchar c);

                virtual void reset();

                virtual JPrimitiveCharArray* toCharArray();

                virtual jint size();

                virtual JString* toString();

                virtual void flush();

                virtual void close();

                virtual ~JCharArrayWriter();
        };
    }
}

#endif
