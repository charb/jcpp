#ifndef JCPP_IO_JOUTPUTSTREAM_H
#define JCPP_IO_JOUTPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/io/JCloseable.h"
#include "jcpp/io/JFlushable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.OutputStream", simpleName="OutputStream");
        class JCPP_EXPORT JOutputStream : public JObject, public JCloseable, public JFlushable{
        protected:
            JOutputStream(jcpp::lang::JClass* _class);

        public:
            JOutputStream();

            static jcpp::lang::JClass* getClazz();

            virtual void write(jint b)=0;

            virtual void write(JPrimitiveByteArray* b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void flush();

            virtual void close();
 
            virtual ~JOutputStream();
        };
    }
}

#endif
