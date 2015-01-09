#ifndef JCPP_IO_JOUTPUTSTREAMWRITER_H
#define JCPP_IO_JOUTPUTSTREAMWRITER_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JWriter.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/nio/cs/JStreamEncoder.h"
#include "jcpp/lang/JNullPointerException.h"

using namespace jcpp::lang;
using namespace jcpp::nio::cs;

//TODO use encoding
namespace jcpp{
    namespace io{
    	class JPrintStream;

    	//@Class(canonicalName="java.io.OutputStreamWriter", simpleName="OutputStreamWriter");
        class JCPP_EXPORT JOutputStreamWriter : public JWriter  {
        	private:
    			JStreamEncoder* se;

            protected:
                JOutputStreamWriter(jcpp::lang::JClass* _class,JOutputStream* out);
                friend class JPrintStream;

            public:
                static jcpp::lang::JClass* getClazz();

                JOutputStreamWriter(JOutputStream* out,JString* encoding);

                JOutputStreamWriter(JOutputStream* out);

                virtual void write(jint i);

                virtual void write(JPrimitiveCharArray* c,jint offset,jint length);

                virtual void write(JString* c,jint offset,jint length);

                virtual void flush();

                virtual void close();

                virtual ~JOutputStreamWriter();
        };
    }
}

#endif
