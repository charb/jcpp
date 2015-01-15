#ifndef JCPP_IO_JDATAOUTPUTSTREAM_H
#define JCPP_IO_JDATAOUTPUTSTREAM_H

#include "jcpp/io/JOutputStream.h"
#include "jcpp/io/JFilterOutputStream.h"
#include "jcpp/io/JDataOutput.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.DataOutputStream", simpleName="DataOutputStream");
        class JCPP_EXPORT JDataOutputStream : public JFilterOutputStream, public JDataOutput{
        private:
            JPrimitiveByteArray* bytearr;
            JPrimitiveByteArray* writeBuffer;
            jint written;
            void incCount(jint value);
            virtual jint writeUTF(JString* str, JDataOutput* out);

        public:
            JDataOutputStream();

            JDataOutputStream(JOutputStream* out);

            static jcpp::lang::JClass* getClazz();

            virtual void write(jint b);

            virtual void write(JPrimitiveByteArray* b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void flush() ;

            virtual void close();

            virtual void writeBoolean(jbool v);

            virtual void writeByte(jint v);

            virtual void writeShort(jint v);

            virtual void writeChar(jint v);

            virtual void writeInt(jint v);

            virtual void writeLong(jlong v);

            virtual void writeFloat(jfloat v);

            virtual void writeDouble(jdouble v);

            virtual void writeBytes(JString* s);

            virtual void writeChars(JString* s);

            virtual void writeUTF(JString* str);

            virtual jint size();

            virtual ~JDataOutputStream();
        };
    }
}

#endif
