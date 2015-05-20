#ifndef JCPP_IO_JBLOCKDATAINPUTSTREAM_H
#define JCPP_IO_JBLOCKDATAINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JObjectStreamConstants.h"
#include "jcpp/io/JBits.h"
#include "jcpp/io/JDataInput.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/io/JPeekInputStream.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveShortArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JPrimitiveDoubleArray.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.ObjectInputStream$BlockDataInputStream", simpleName="ObjectInputStream$BlockDataInputStream");
        class JCPP_EXPORT JBlockDataInputStream : public JInputStream, public JObjectStreamConstants, public JDataInput {
        private:
            static const jint IN_MAX_BLOCK_SIZE = 1024;
            static const jint IN_MAX_HEADER_SIZE = 5;
            static const jint IN_CHAR_BUF_SIZE = 256;
            static const jint IN_HEADER_BLOCKED = -2;
        protected:
            JPrimitiveByteArray* buf;
            JPrimitiveByteArray* hbuf;
            JPrimitiveCharArray* cbuf;
            jbool blkmode;
            jint pos;
            jint end;
            jint unread;
            JPeekInputStream *in;
            JDataInputStream *din;
            jbool defaultDataEnd;

            jbool setBlockDataMode(jbool newmode);
            jbool getBlockDataMode();
            void skipBlockData();
            jint readBlockHeader(jbool canBlock);
            void refill();
            jint currentBlockRemaining() ;
            jint peek();
            jbyte peekByte();
            jint read(JPrimitiveByteArray* b, jint off, jint len, jbool copy);
            void readBooleans(JPrimitiveBooleanArray *v, jint off, jint len);
            void readChars(JPrimitiveCharArray* v, jint off, jint len);
            void readShorts(JPrimitiveShortArray *v, jint off, jint len);
            void readInts(JPrimitiveIntArray *v, jint off, jint len);
            void readFloats(JPrimitiveFloatArray *v, jint off, jint len);
            void readLongs(JPrimitiveLongArray *v, jint off, jint len);
            void readDoubles(JPrimitiveDoubleArray *v, jint off, jint len);
            JString* readLongUTF();
            JString* readUTFBody(jlong len);
            jlong readUTFSpan(JStringBuilder* sbuf, jlong utflen);
            jint readUTFChar(JStringBuilder* sbuf, jlong utflen);
            jbool isDefaultDataEnd();
            void setDefaultDataEnd(jbool defaultDataEnd);
            friend class JObjectInputStream;

        public:
            JBlockDataInputStream(JInputStream *in);

            static jcpp::lang::JClass* getClazz();

            virtual jint read();

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual jlong skip(jlong len);

            virtual jint available();

            virtual void close();

            virtual void readFully(JPrimitiveByteArray* b);

            virtual void readFully(JPrimitiveByteArray* b, jint off, jint len);

            virtual void readFully(JPrimitiveByteArray* b, jint off, jint len, jbool copy);

            virtual jint skipBytes(jint n);

            virtual jbool readBoolean();

            virtual jbyte readByte();

            virtual jint readUnsignedByte();

            virtual jchar readChar();

            virtual jshort readShort();

            virtual jint readUnsignedShort();

            virtual jint readInt();

            virtual jfloat readFloat();

            virtual jlong readLong();
            
            virtual jdouble readDouble();

            virtual JString* readUTF();
            
            virtual ~JBlockDataInputStream();
        };
    }
}

#endif
