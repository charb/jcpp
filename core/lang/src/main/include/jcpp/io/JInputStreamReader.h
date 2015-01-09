#ifndef JCPP_IO_JINPUTSTREAMREADER_H
#define JCPP_IO_JINPUTSTREAMREADER_H

#include "jcpp/io/JReader.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/nio/cs/JStreamDecoder.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.InputStreamReader", simpleName="InputStreamReader");
        class JCPP_EXPORT JInputStreamReader : public JReader  {
        	private:
        		JStreamDecoder* sd;

        	protected:
                JInputStreamReader(jcpp::lang::JClass* _class,JInputStream* in);

            public:
                static jcpp::lang::JClass* getClazz();

                JInputStreamReader(JInputStream* in);

                JInputStreamReader(JInputStream* in, JString* charsetName);

                JInputStreamReader(JInputStream* in, JCharset* cs);

                JInputStreamReader(JInputStream* in, JCharsetDecoder* dec);

                JString* getEncoding();

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* cbuf,jint offset, jint length);

                virtual jbool ready();

                virtual void close();

                virtual ~JInputStreamReader();
        };
    }
}

#endif 
