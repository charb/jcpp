#ifndef JCPP_IO_JFILTEROUTPUTSTREAM_H
#define JCPP_IO_JFILTEROUTPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FilterOutputStream", simpleName="FilterOutputStream");
        class JCPP_EXPORT JFilterOutputStream : public JOutputStream{
        protected:
            JOutputStream* out;
            JFilterOutputStream(JOutputStream* out,jcpp::lang::JClass* _class);

        public:
            static jcpp::lang::JClass* getClazz();

            virtual void write(jint b);

            virtual void write(JPrimitiveByteArray* b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void flush();

            virtual void close();

            virtual ~JFilterOutputStream();
        };
    }
}

#endif
