#ifndef JCPP_IO_JFILTERWRITER_H
#define JCPP_IO_JFILTERWRITER_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FilterWriter", simpleName="FilterWriter");
        class JCPP_EXPORT JFilterWriter : public JWriter  {
            protected:
                JWriter* out;
                JFilterWriter(jcpp::lang::JClass* _class,JWriter* out);

            public:
                static jcpp::lang::JClass* getClazz();

                virtual void write(jint c);

                virtual void write(JPrimitiveCharArray* cbuf, jint off, jint len);

                virtual void write(JString* str, jint off, jint len);

                virtual void flush();

                virtual void close();

                virtual ~JFilterWriter();
        };
    }
}

#endif
