#ifndef JCPP_IO_JDATAINPUTSTREAM_H
#define JCPP_IO_JDATAINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFilterInputStream.h"
#include "jcpp/io/JDataInput.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{


        //@Class(canonicalName="java.io.DataInputStream", simpleName="DataInputStream");
    	class JCPP_EXPORT JDataInputStream : public JFilterInputStream, public JDataInput{
        protected:
            JPrimitiveByteArray* bytearr;
            JPrimitiveCharArray* chararr;
            JPrimitiveByteArray* readBuffer;
            void setInputStream(JInputStream *in);

        public:
            JDataInputStream();

            JDataInputStream(JInputStream *in);

            static jcpp::lang::JClass* getClazz();

            virtual jint read(JPrimitiveByteArray* b);

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual void readFully(JPrimitiveByteArray* b);

            virtual void readFully(JPrimitiveByteArray* b, jint off, jint len);

            virtual jint skipBytes(jint n);

            virtual jbool readBoolean();

            virtual jbyte readByte();

            virtual jint readUnsignedByte();

            virtual jshort readShort();

            virtual jint readUnsignedShort();

            virtual jchar readChar();

            virtual jint readInt();

            virtual jlong readLong();

            virtual jfloat readFloat();

            virtual jdouble readDouble();

            virtual JString* readUTF();

            static JString* readUTF(JDataInput* in);

            virtual ~JDataInputStream();
        };
    }
}

#endif
