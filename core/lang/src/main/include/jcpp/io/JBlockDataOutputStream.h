#ifndef JCPP_IO_BLOCKDATAOUTPUTSTREAM_H
#define JCPP_IO_BLOCKDATAOUTPUTSTREAM_H

#include "jcpp/io/JOutputStream.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JBits.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JDataOutput.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveShortArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JPrimitiveDoubleArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JObjectOutputStream;
        class JPutFieldImpl;

        //@Class(canonicalName="java.io.ObjectOutputStream$BlockDataOutputStream", simpleName="ObjectOutputStream$BlockDataOutputStream");
        class JCPP_EXPORT JBlockDataOutputStream : public JOutputStream, public JDataOutput{
        protected:
            static const jint MAX_BLOCK_SIZE = 1024;
            static const jint MAX_HEADER_SIZE = 5;
            static const jint CHAR_BUF_SIZE = 256;

            JPrimitiveByteArray* buf;
            JPrimitiveByteArray* hbuf;
            JPrimitiveCharArray* cbuf;
            jbool blkmode;
            jint pos;
            JOutputStream* out;
            JDataOutputStream* dout;
            
            jbool setBlockDataMode(jbool mode);
            jbool getBlockDataMode();
            void write(JPrimitiveByteArray* b, jint off, jint len, jbool copy);
            void drain();
            void writeBlockHeader(jint len);
            void writeBooleans(JPrimitiveBooleanArray* v, jint off, jint len);
            void writeChars(JPrimitiveCharArray* v, jint off, jint len);
            void writeShorts(JPrimitiveShortArray* v, jint off, jint len);
            void writeInts(JPrimitiveIntArray* v, jint off, jint len);
            void writeFloats(JPrimitiveFloatArray* v, jint off, jint len);
            void writeLongs(JPrimitiveLongArray* v, jint off, jint len);
            void writeDoubles(JPrimitiveDoubleArray* v, jint off, jint len);
            jlong getUTFLength(JString* s);
            void writeUTF(JString* s, jlong utflen);
            void writeLongUTF(JString* s);
            void writeLongUTF(JString* s, jlong utflen);
            void writeUTFBody(JString* s);
            friend class JObjectOutputStream;
            friend class JPutFieldImpl;

        public:
            JBlockDataOutputStream(JOutputStream* out);

            static jcpp::lang::JClass* getClazz();

            virtual void write(jint b);

            virtual void write(JPrimitiveByteArray* b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void flush();

            virtual void close();

            virtual void writeBoolean(jbool v);

            virtual void writeByte(jint v);

            virtual void writeChar(jint v);

            virtual void writeShort(jint v);

            virtual void writeInt(jint v);

            virtual void writeFloat(jfloat v);

            virtual void writeLong(jlong v);
            
            virtual void writeDouble(jdouble v);
            
            virtual void writeBytes(JString* s);
            
            virtual void writeChars(JString* s);

            virtual void writeUTF(JString* s);
            
            virtual ~JBlockDataOutputStream();
        };
    }
}

#endif
