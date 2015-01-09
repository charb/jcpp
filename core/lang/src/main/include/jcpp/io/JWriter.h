#ifndef JCPP_IO_JWRITER_H
#define JCPP_IO_JWRITER_H

#include "jcpp/io/JFlushable.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JCloseable.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.Writer", simpleName="Writer");
        class JCPP_EXPORT JWriter : public JObject  , public JAppendable  , public JCloseable  , public JFlushable  {
            protected:
                JPrimitiveCharArray* writeBuffer;
                JObject* lock;
                JWriter(jcpp::lang::JClass* _class);
                JWriter(jcpp::lang::JClass* _class,JObject* lock);

            public:
                static jcpp::lang::JClass* getClazz();

                virtual void write(jint c);

                virtual void write(JPrimitiveCharArray* c);

                virtual void write(JPrimitiveCharArray* c,jint offset,jint length)=0;

                virtual void write(JString* str);

                virtual void write(JString* str,jint off,jint len);

                virtual JWriter* append(JCharSequence* p0 );

                virtual JWriter* append(JCharSequence* p0, jint start, jint end);

                virtual JWriter* append(jchar c);

                virtual void flush()=0;

                virtual void close()=0;

                virtual ~JWriter();
        };
    }
}

#endif
