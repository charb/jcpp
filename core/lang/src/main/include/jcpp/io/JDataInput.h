#ifndef JCPP_IO_JDATAINPUT_H
#define JCPP_IO_JDATAINPUT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.ObjectOutputStream", simpleName="ObjectOutputStream");
        class JCPP_EXPORT JDataInput : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual void readFully(JPrimitiveByteArray* b)=0;

            virtual void readFully(JPrimitiveByteArray* b,jint off,jint len)=0;

            virtual jint skipBytes(jint n)=0;

            virtual jbool readBoolean()=0;

            virtual jbyte readByte()=0;

            virtual jint readUnsignedByte()=0;

            virtual jshort readShort()=0;

            virtual jint readUnsignedShort()=0;

            virtual jchar readChar()=0;

            virtual jint readInt()=0;

            virtual jlong readLong()=0;

            virtual jfloat readFloat()=0;

            virtual jdouble readDouble()=0;

            virtual JString* readUTF()=0;

            virtual ~JDataInput();
        };
    }
}

#endif
