#include "jcpp/io/JDataInputStream.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/io/JEOFException.h"
#include "jcpp/io/JUTFDataFormatException.h"
#include "jcpp/io/JBits.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JDataInputStream::JDataInputStream():JFilterInputStream(null,getClazz()){
            bytearr=new JPrimitiveByteArray(80);
            chararr=new JPrimitiveCharArray(80);
            readBuffer=new JPrimitiveByteArray(8);
        }

        JDataInputStream::JDataInputStream(JInputStream *in):JFilterInputStream(in,getClazz()){
            bytearr=new JPrimitiveByteArray(80);
            chararr=new JPrimitiveCharArray(80);
            readBuffer=new JPrimitiveByteArray(8);
        }

        void JDataInputStream::setInputStream(JInputStream *in){
            this->in=in;
        }

        jint JDataInputStream::read(JPrimitiveByteArray* b) {
            return in->read(b,0,b->size());
        }

        jint JDataInputStream::read(JPrimitiveByteArray* b, jint off, jint len) {
            return in->read(b,off,len);
        }

        void JDataInputStream::readFully(JPrimitiveByteArray* b) {
            readFully(b, 0,b->size());
        }

        void JDataInputStream::readFully(JPrimitiveByteArray* b, jint off, jint len) {
            if (len < 0){
                throw new JIndexOutOfBoundsException;
            }
            jint n = 0;
            while (n < len) {
                jint count = in->read(b, off + n, len - n);
                if (count < 0){
                    throw new JEOFException();
                }
                n += count;
            }
        }

        jint JDataInputStream::skipBytes(jint n){
            jint total = 0;
            jint cur = 0;

            while ((total<n) && ((cur = (jint) in->skip(n-total)) > 0)) {
                total += cur;
            }
            return total;
        }

        jbool JDataInputStream::readBoolean() {
            jint b=in->read();
            if (b<0){
                throw new JEOFException();
            }
            return b!=0;
        }

        jbyte JDataInputStream::readByte() {
            jint b=in->read();
            if (b<0){
                throw new JEOFException();
            }
            return (jbyte)b;
        }

        jint JDataInputStream::readUnsignedByte() {
            jint b=in->read();
            if (b<0){
                throw new JEOFException();
            }
            return b;
        }

        jshort JDataInputStream::readShort() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return (jshort)((ch1 << 8) + (ch2 << 0));
        }

        jint JDataInputStream::readUnsignedShort() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            jint result=((ch1 << 8) + (ch2 << 0));
            return result;
        }

        jchar JDataInputStream::readChar() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            if ((ch1 | ch2) < 0){
                throw new JEOFException();
            }
            return (jchar)((ch1 << 8) + (ch2 << 0));
        }

        jint JDataInputStream::readInt() {
            jint ch1 = in->read();
            jint ch2 = in->read();
            jint ch3 = in->read();
            jint ch4 = in->read();
            if ((ch1 | ch2 | ch3 | ch4) < 0){
                throw new JEOFException();
            }
            return ((ch1 << 24) + (ch2 << 16) + (ch3 << 8) + (ch4 << 0));
        }

        jlong JDataInputStream::readLong() {
            readFully(readBuffer, 0, 8);
            jlong l=( ((jlong)readBuffer->getByte(0) << 56) + ((jlong)(readBuffer->getByte(1) & 255) << 48) +
                      ((jlong)(readBuffer->getByte(2) & 255) << 40) + ((jlong)(readBuffer->getByte(3) & 255) << 32) +
                      ((jlong)(readBuffer->getByte(4) & 255) << 24) + ((readBuffer->getByte(5) & 255) << 16) +
                      ((readBuffer->getByte(6) & 255) <<  8) + ((readBuffer->getByte(7) & 255) <<  0));
            return l;
        }

        jfloat JDataInputStream::readFloat() {
            readFully(readBuffer,0,4);
            return JBits::getFloat(readBuffer,0);
        }

        jdouble JDataInputStream::readDouble() {
            readFully(readBuffer,0,8);
            return JBits::getDouble(readBuffer,0);
        }

        JString* JDataInputStream::readUTF() {
            return readUTF(this);
        }

        JString* JDataInputStream::readUTF(JDataInput* in) {
            jshort utflen = in->readUnsignedShort();
            JPrimitiveByteArray* bytearr = null;
            JPrimitiveCharArray* chararr = null;

            if (in->getClazz()->isAssignableFrom(JDataInputStream::getClazz())) {
                JDataInputStream* dis = dynamic_cast<JDataInputStream*>(in);
                if (dis->bytearr->size() < utflen){
                    dis->bytearr = new JPrimitiveByteArray(utflen*2);
                    dis->chararr = new JPrimitiveCharArray(utflen*2);
                }
                chararr = dis->chararr;
                bytearr = dis->bytearr;
            } else {
                bytearr = new JPrimitiveByteArray(utflen);
                chararr = new JPrimitiveCharArray(utflen);
            }

            jint c=0;
            jint char2=0;
            jint char3=0;
            jint count = 0;
            jint chararr_count = 0;

            in->readFully(bytearr, 0, utflen);

            while (count < utflen) {
                c = (jint) bytearr->getByte(count) & 0xff;
                if (c > 127){
                    break;
                }
                count++;
                chararr->setChar(chararr_count++,(jchar)c);
            }

            while (count < utflen) {
                c = (jint) bytearr->getByte(count) & 0xff;
                switch (c >> 4) {
                case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
                    /* 0xxxxxxx*/
                    count++;
                    chararr->setChar(chararr_count++,(jchar)c);
                    break;
                case 12: case 13:
                    /* 110x xxx  10xx xxx*/
                    count += 2;
                    if (count > utflen){
                        throw new JUTFDataFormatException(new JString("malformed input: partial character at end"));
                    }
                    char2 = (jint) bytearr->getByte(count-1);
                    if ((char2 & 0xC0) != 0x80){
                        throw new JUTFDataFormatException(new JString("malformed input around byte "));
                    }
                    chararr->setChar(chararr_count++,(jchar)(((c & 0x1F) << 6) | (char2 & 0x3F)));
                    break;
                case 14:
                    /* 1110 xxxx  10xx xxxx  10xx xxxx */
                    count += 3;
                    if (count > utflen){
                        throw new JUTFDataFormatException(new JString("malformed input: partial character at end"));
                    }
                    char2 = (jint) bytearr->getByte(count-2);
                    char3 = (jint) bytearr->getByte(count-1);
                    if (((char2 & 0xC0) != 0x80) || ((char3 & 0xC0) != 0x80))
                        throw new JUTFDataFormatException(new JString("malformed input around byte "));
                    chararr->setChar(chararr_count++,  (jchar) (((c     & 0x0F) << 12) |
                                                       ((char2 & 0x3F) << 6)  |
                                                       ((char3 & 0x3F) << 0)));
                    break;
                default:
                    /* 10xx xxxx,  1111 xxxx */
                    throw new JUTFDataFormatException(new JString("malformed input around byte "));
                }
            }

            return new JString(chararr,0,chararr_count);
        }

        JDataInputStream::~JDataInputStream() {
        }
    }
}
