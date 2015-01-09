#ifndef JCPP_IO_JOBJECTOUTPUT_H
#define JCPP_IO_JOBJECTOUTPUT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JDataOutput.h"
#include "jcpp/lang/JAutoCloseable.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectOutput", simpleName="ObjectOutput");
        class JCPP_EXPORT JObjectOutput : public JDataOutput, public JAutoCloseable{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual void writeObject(JObject* object)=0;

            virtual void write(jint b)=0;

            virtual void write(JPrimitiveByteArray* b)=0;

            virtual void write(JPrimitiveByteArray* b, jint off, jint len)=0;

            virtual void flush()=0;

            virtual void close()=0;

            virtual ~JObjectOutput();
        };
    }
}

#endif
