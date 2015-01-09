#ifndef JCPP_IO_JDATAOUTPUT_H
#define JCPP_IO_JDATAOUTPUT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.DataOutput", simpleName="DataOutput");
        class JCPP_EXPORT JDataOutput : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual void write(jint b)=0;

            virtual void write(JPrimitiveByteArray* b)=0;

            virtual void write(JPrimitiveByteArray* b, jint off, jint len)=0;

            virtual void writeBoolean(jbool v)=0;

            virtual void writeByte(jint v)=0;

            virtual void writeShort(jint v)=0;

            virtual void writeChar(jint v)=0;

            virtual void writeInt(jint v)=0;

            virtual void writeLong(jlong v)=0;

            virtual void writeFloat(jfloat v)=0;

            virtual void writeDouble(jdouble v)=0;

            virtual void writeBytes(JString* s)=0;

            virtual void writeChars(JString* s)=0;

            virtual void writeUTF(JString* str)=0;

            virtual ~JDataOutput();
        };
    }
}

#endif
