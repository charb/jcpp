#ifndef JCPP_IO_JSTRINGREADER_H
#define JCPP_IO_JSTRINGREADER_H

#include "jcpp/io/JReader.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.StringReader", simpleName="StringReader");
        class JCPP_EXPORT JStringReader : public JReader  {
            protected:
                JString* str;
                jint length;
                jint next;
                jint imark;

            public:
                static jcpp::lang::JClass* getClazz();

                JStringReader(JString* s);

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual jlong skip(jlong n);

                virtual jbool ready();

                virtual jbool markSupported();

                virtual void mark(jint m);

                virtual void reset();

                virtual void close();

                virtual ~JStringReader();
        };
    }
}

#endif
