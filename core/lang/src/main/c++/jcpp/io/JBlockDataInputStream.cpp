#include "jcpp/io/JBlockDataInputStream.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/io/JStreamCorruptedException.h"
#include "jcpp/io/JEOFException.h"
#include "jcpp/io/JUTFDataFormatException.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JDataInput.h"
#include "jcpp/io/JPeekInputStream.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

namespace jcpp{
    namespace io{

        static const jint IN_MAX_BLOCK_SIZE = 1024;
        static const jint IN_MAX_HEADER_SIZE = 5;
        static const jint IN_CHAR_BUF_SIZE = 256;
        static const jint IN_HEADER_BLOCKED = -2;

        JBlockDataInputStream::JBlockDataInputStream(JInputStream *in): JInputStream(getClazz()) {
            defaultDataEnd=false;
            buf=new JPrimitiveByteArray(IN_MAX_BLOCK_SIZE);
            hbuf=new JPrimitiveByteArray(IN_MAX_HEADER_SIZE);
            cbuf=new JPrimitiveCharArray(IN_CHAR_BUF_SIZE);
            this->blkmode=false;
            this->pos=0;
            this->end=-1;
            this->unread=0;
            this->in = new JPeekInputStream(in);
            this->din = new JDataInputStream(this);
        }

        jbool JBlockDataInputStream::setBlockDataMode(jbool newmode) {
            if (blkmode == newmode) {
                return blkmode;
            }
            if (newmode) {
                pos = 0;
                end = 0;
                unread = 0;
            }else if (pos < end) {
                throw new JIllegalStateException(new JString("unread block dat"));
            }
            blkmode = newmode;
            return !blkmode;
        }

        jbool JBlockDataInputStream::getBlockDataMode() {
            return blkmode;
        }

        void JBlockDataInputStream::skipBlockData() {
            if (!blkmode) {
                throw new JIllegalStateException(new JString("not in block data mode"));
            }
            while (end >= 0) {
                refill();
            }
        }

        jint JBlockDataInputStream::readBlockHeader(jbool canBlock) {
            if (defaultDataEnd) {
                return -1;
            }
            for (;;) {
                jlong avail;
                if (canBlock) {
                    avail = JInteger::MAX_VALUE;;
                }else {
                    avail = in->available();
                }
                if (avail == 0) {
                    return IN_HEADER_BLOCKED;
                }

                jbyte tc = in->peek();
                switch (tc) {
                    case JObjectStreamConstants::TC_BLOCKDATA:
                        if (avail < 2) {
                            return IN_HEADER_BLOCKED;
                        }
                        in->readFully(hbuf,0,2);
                        return hbuf->getByte(1) & 0xFF;

                    case JObjectStreamConstants::TC_BLOCKDATALONG:{
                        if (avail < 5) {
                            return IN_HEADER_BLOCKED;
                        }
                        in->readFully(hbuf,0,5);
                        jint len = JBits::getInt(hbuf,1);
                        if (len < 0) {
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append("illegal block data header length: ")->append(len);
                            throw new JStreamCorruptedException(builder->toString());
                        }
                        return len;
                    }

                    case JObjectStreamConstants::TC_RESET:
                        in->read();
                        break;

                    default:
                        if (tc >= 0 && (tc < JObjectStreamConstants::TC_BASE || tc > JObjectStreamConstants::TC_MAX)) {
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append("invalid type code: ")->append(tc);
                            throw new JStreamCorruptedException(builder->toString());
                        }
                        return -1;
                }
            }
        }

        void JBlockDataInputStream::refill() {
            do {
                pos = 0;
                if (unread > 0) {
                    jint n = in->read(buf,0,(unread < IN_MAX_BLOCK_SIZE ? unread : IN_MAX_BLOCK_SIZE));
                    if (n >= 0) {
                        end = n;
                        unread -= n;
                    } else {
                        throw new JStreamCorruptedException(new JString("unexpected EOF in middle of data block"));
                    }

                }else {
                    jint n = readBlockHeader(true);
                    if (n >= 0) {
                        end = 0;
                        unread = n;
                    }else {
                        end = -1;
                        unread = 0;
                    }
                }
            } while (pos == end);
        }

        jint JBlockDataInputStream::currentBlockRemaining() {
            if (blkmode) {
                return (end >= 0) ? (end - pos) + unread : 0;
            }else {
                throw new JIllegalStateException();
            }
        }

        jint JBlockDataInputStream::peek(){
            if (blkmode) {
                if (pos == end) {
                    refill();
                }
                return (end >= 0) ? (buf->getByte(pos) & 0xFF) : -1;
            } else {
                return in->peek();
            }
        }

        jbyte JBlockDataInputStream::peekByte(){
            jint val = peek();
            if (val < 0) {
                throw new JEOFException();
            }
            return (jbyte) val;
        }

        jbool JBlockDataInputStream::isDefaultDataEnd(){
            return defaultDataEnd;
        }

        void JBlockDataInputStream::setDefaultDataEnd(jbool defaultDataEnd){
            this->defaultDataEnd=defaultDataEnd;
        }

        jint JBlockDataInputStream::read() {
            if (blkmode) {
                if (pos == end) {
                    refill();
                }
                return (end >= 0) ? (buf->getByte(pos++) & 0xFF) : -1;
            }else {
                return in->read();
            }
        }

        jint JBlockDataInputStream::read(JPrimitiveByteArray* b, jint off, jint len) {
            return read(b, off, len, false);
        }

        jlong JBlockDataInputStream::skip(jlong len){
            jlong remain = len;
            while (remain > 0) {
                if (blkmode) {
                    if (pos == end) {
                        refill();
                    }
                    if (end < 0) {
                        break;
                    }
                    jint nread = (jint) (remain< end - pos ? remain : end-pos );
                    remain -= nread;
                    pos += nread;
                } else {
                    jint nread = (jint) (remain < IN_MAX_BLOCK_SIZE ? remain : IN_MAX_BLOCK_SIZE);
                    if ((nread = in->read(buf, 0, nread)) < 0) {
                        break;
                    }
                    remain -= nread;
                }
            }
            return len - remain;
        }

        jint JBlockDataInputStream::available() {
            if (blkmode) {
                if ((pos == end) && (unread == 0)) {
                    jint n=0;
                    while ((n = readBlockHeader(false)) == 0);
                    switch (n) {
                    case IN_HEADER_BLOCKED:
                        break;

                    case -1:
                        pos = 0;
                        end = -1;
                        break;

                    default:
                        pos = 0;
                        end = 0;
                        unread = n;
                        break;
                    }
                }
                jint unreadAvail = (unread > 0) ? min(in->available(), unread) : 0;
                return (end >= 0) ? (end - pos) + unreadAvail : 0;
            }else {
                return in->available();
            }
        }

        void JBlockDataInputStream::close() {
            if (blkmode) {
                pos = 0;
                end = -1;
                unread = 0;
            }
            in->close();
        }

        jint JBlockDataInputStream::read(JPrimitiveByteArray* b, jint off, jint len, jbool copy) {
            if (len == 0) {
                return 0;
            }else if (blkmode) {
                if (pos == end) {
                    refill();
                }
                if (end < 0) {
                    return -1;
                }
                jint nread = min(len, end - pos);
                JSystem::arraycopy(buf, pos, b, off, nread);
                pos += nread;
                return nread;
            }else if (copy) {
                jint nread = in->read(buf,0,min(len, IN_MAX_BLOCK_SIZE));
                if (nread > 0) {
                    JSystem::arraycopy(buf, 0, b, off, nread);
                }
                return nread;
            }else {
                return in->read(b,off,len);
            }
        }

        void JBlockDataInputStream::readFully(JPrimitiveByteArray *b) {
            readFully(b, 0, b->size(), false);
        }

        void JBlockDataInputStream::readFully(JPrimitiveByteArray *b, jint off, jint len) {
            readFully(b, off, len, false);
        }

        void JBlockDataInputStream::readFully(JPrimitiveByteArray *b, jint off, jint len, jbool copy) {
            while (len > 0) {
                jint n = read(b, off, len, copy);
                if (n < 0) {
                    throw new JEOFException();
                }
                off += n;
                len -= n;
            }
        }

        jint JBlockDataInputStream::skipBytes(jint n){
            return din->skipBytes(n);
        }

        jbool JBlockDataInputStream::readBoolean() {
            jint v = read();
            if (v < 0) {
                throw new JEOFException();
            }
            return (v != 0);
        }

        jbyte JBlockDataInputStream::readByte() {
            jint v = read();
            if (v < 0) {
                throw new JEOFException();
            }
            return (jbyte) v;
        }

        jint JBlockDataInputStream::readUnsignedByte() {
            jint v = read();
            if (v < 0) {
                throw new JEOFException();
            }
            return v;
        }

        jchar JBlockDataInputStream::readChar() {
            if (!blkmode) {
               pos = 0;
               in->readFully(buf, 0, 2);
           } else if (end - pos < 2) {
                return din->readChar();
           }
           jchar v = JBits::getChar(buf, pos);
           pos += 2;
           return v;
        }

        jshort JBlockDataInputStream::readShort() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf,0,2);

            }else if ( end - pos < 2) {
                return din->readShort();
            }
            jshort v = JBits::getShort(buf, pos);
            pos += 2;
            return v;
        }

        jint JBlockDataInputStream::readUnsignedShort(){
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 2);
            } else if (end - pos < 2) {
                jint v=din->readUnsignedShort();
                return v;
            }
            jint v = JBits::getShort(buf, pos) & 0xFFFF;
            pos += 2;
            return v;
        }

        jint JBlockDataInputStream::readInt() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 4);

            } else if (end - pos < 4) {
                return din->readInt();
            }
            jint v = JBits::getInt(buf, pos);
            pos += 4;
            return v;
        }

        jfloat JBlockDataInputStream::readFloat() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 4);

            }else if (end - pos < 4) {
                return din->readFloat();
            }
            jfloat v = JBits::getFloat(buf, pos);
            pos += 4;
            return v;
        }

        jlong JBlockDataInputStream::readLong() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 8);

            }else if (end - pos < 8) {
                return din->readLong();
            }
            jlong v = JBits::getLong(buf, pos);
            pos += 8;
            return v;
        }

        jdouble JBlockDataInputStream::readDouble() {
            if (!blkmode) {
                pos = 0;
                in->readFully(buf, 0, 8);

            } else if (end - pos < 8) {
                return din->readDouble();
            }
            jdouble v = JBits::getDouble(buf, pos);
            pos += 8;
            return v;
        }

        JString* JBlockDataInputStream::readUTF() {
            jint i=readUnsignedShort();
            JString* str=readUTFBody(i);
            return str;
        }
        
        void JBlockDataInputStream::readBooleans(JPrimitiveBooleanArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off+ len;
            while(off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE);
                    in->readFully(buf,0, span);
                    stop = off + span;
                    pos = 0;
                }else if (end - pos < 1) {
                    v->setBoolean(off++,din->readBoolean());
                    continue;
                }else {
                    stop = min(endoff, off + end - pos);
                }
                while (off < stop) {
                    v->setBoolean(off++,JBits::getBoolean(buf, pos++));
                }
            }
        }

        void JBlockDataInputStream::readChars(JPrimitiveCharArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off+ len;
            while(off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE >> 1);
                    in->readFully(buf,0, span << 1);
                    stop = off + span;
                    pos = 0;
                }else if (end - pos < 2) {
                    v->setChar(off++,din->readChar());
                    continue;
                }else {
                    stop = min(endoff, off + ((end - pos) >> 1));
                }
                while (off < stop) {
                    v->setChar(off++,JBits::getChar(buf,pos));
                    pos += 2;
                }
            }
        }

        void JBlockDataInputStream::readShorts(JPrimitiveShortArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE >> 1);
                    in->readFully(buf, 0,span << 1);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 2) {
                    v->setShort(off++,din->readShort());
                    continue;
                } else {
                    stop = min(endoff, off + ((end - pos) >> 1));
                }

                while (off < stop) {
                    v->setShort(off++,JBits::getShort(buf, pos));
                    pos += 2;
                }
            }
        }

        void JBlockDataInputStream::readInts(JPrimitiveIntArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE >> 2);
                    in->readFully(buf, 0, span << 2);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 4) {
                    v->setInt(off++,din->readInt());
                    continue;
                } else {
                    stop = min(endoff, off + ((end - pos) >> 2));
                }

                while (off < stop) {
                    v->setInt(off++,JBits::getInt(buf, pos));
                    pos += 4;
                }
            }
        }

        void JBlockDataInputStream::readFloats(JPrimitiveFloatArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE >> 2);
                    in->readFully(buf, 0, span << 2);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 4) {
                    v->setFloat(off++,din->readFloat());
                    continue;
                } else {
                    stop = min(endoff, off + ((end - pos) >> 2));
                }

                while (off < stop) {
                    v->setFloat(off++,JBits::getFloat(buf,pos));
                    pos += 4;
                }
            }
        }

        void JBlockDataInputStream::readLongs(JPrimitiveLongArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE >> 3);
                    in->readFully(buf, 0, span << 3);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 8) {
                    v->setLong(off++,din->readLong());
                    continue;
                } else {
                    stop = min(endoff, off + ((end - pos) >> 3));
                }

                while (off < stop) {
                    v->setLong(off++,JBits::getLong(buf, pos));
                    pos += 8;
                }
            }
        }

        void JBlockDataInputStream::readDoubles(JPrimitiveDoubleArray *v, jint off, jint len) {
            jint stop=0;
            jint endoff = off + len;
            while (off < endoff) {
                if (!blkmode) {
                    jint span = min(endoff - off, IN_MAX_BLOCK_SIZE >> 3);
                    in->readFully(buf, 0, span << 3);
                    stop = off + span;
                    pos = 0;
                } else if (end - pos < 8) {
                    v->setDouble(off++,din->readDouble());
                    continue;
                } else {
                    stop = min(endoff - off, ((end - pos) >> 3));
                }

                while (off < stop) {
                    v->setDouble(off++,JBits::getDouble(buf, pos));
                    pos += 8;
                }
            }
        }

        JString* JBlockDataInputStream::readLongUTF() {
            return readUTFBody(readLong());
        }

        JString* JBlockDataInputStream::readUTFBody(jlong utflen) {
            JStringBuilder* sbuf=new JStringBuilder();
            if (!blkmode) {
                end = pos = 0;
            }

            while (utflen > 0) {
                jint avail = end - pos;
                if (avail >= 3 || (jlong) avail == utflen) {
                    utflen -= readUTFSpan(sbuf, utflen);
                } else {
                    if (blkmode) {
                        utflen -= readUTFChar(sbuf, utflen);
                    } else {
                        if (avail > 0) {
                            JSystem::arraycopy(buf, pos, buf, 0, avail);
                        }
                        pos = 0;
                        end = (jint) min(IN_MAX_BLOCK_SIZE,(jint) utflen);
                        in->readFully(buf, avail, end - avail);
                    }
                }
            }
            return sbuf->toString();
        }

        jlong JBlockDataInputStream::readUTFSpan(JStringBuilder* sbuf, jlong utflen) {
            jint cpos = 0;
            jint start = pos;
            jint avail = min(end - pos, IN_CHAR_BUF_SIZE);
            jint stop = pos + ((utflen > avail) ? avail - 2 : (jint) utflen);
            jbool outOfBounds = false;

            try {
                while (pos < stop) {
                    jint b1=0;
                    jint b2=0;
                    jint b3=0;
                    b1 = buf->getByte(pos++) & 0xFF;
                    switch (b1 >> 4) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:	  // 1 byte format: 0xxxxxxx
                            cbuf->setChar(cpos++,(jchar) b1);
                            break;

                        case 12:
                        case 13:  // 2 byte format: 110xxxxx 10xxxxxx
                            b2 = buf->getByte(pos++);
                            if ((b2 & 0xC0) != 0x80) {
                                throw new JUTFDataFormatException();
                            }
                            cbuf->setChar(cpos++,(jchar) (((b1 & 0x1F) << 6) |  ((b2 & 0x3F) << 0)));
                            break;

                        case 14:  // 3 byte format: 1110xxxx 10xxxxxx 10xxxxxx
                            b3 = buf->getByte(pos + 1);
                            b2 = buf->getByte(pos + 0);
                            pos += 2;
                            if ((b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) {
                                throw new JUTFDataFormatException();
                            }
                            cbuf->setChar(cpos++, (jchar) (((b1 & 0x0F) << 12) |  ((b2 & 0x3F) << 6) |  ((b3 & 0x3F) << 0)));
                            break;

                        default:  // 10xx xxxx, 1111 xxxx
                            throw new JUTFDataFormatException();
                    }
                }
            } catch (JArrayIndexOutOfBoundsException* ex){
                outOfBounds = true;
            }
            if (outOfBounds || (pos - start) > utflen) {
                pos = start + (jint) utflen;
                throw new JUTFDataFormatException();
            }
            sbuf->append(cbuf, 0, cpos);
            return pos - start;
        }

        jint JBlockDataInputStream::readUTFChar(JStringBuilder* sbuf, jlong utflen){
            jint b1=0;
            jint b2=0;
            jint b3=0;
            b1 = readByte() & 0xFF;
            switch (b1 >> 4) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:     // 1 byte format: 0xxxxxxx
                    sbuf->append((jchar) b1);
                    return 1;

                case 12:
                case 13:    // 2 byte format: 110xxxxx 10xxxxxx
                    if (utflen < 2) {
                        throw new JUTFDataFormatException();
                    }
                    b2 = readByte();
                    if ((b2 & 0xC0) != 0x80) {
                        throw new JUTFDataFormatException();
                    }
                    sbuf->append((jchar) (((b1 & 0x1F) << 6) | ((b2 & 0x3F) << 0)));
                    return 2;

                case 14:    // 3 byte format: 1110xxxx 10xxxxxx 10xxxxxx
                    if (utflen < 3) {
                        if (utflen == 2) {
                            readByte();		// consume remaining byte
                        }
                        throw new JUTFDataFormatException();
                    }
                    b2 = readByte();
                    b3 = readByte();
                    if ((b2 & 0xC0) != 0x80 || (b3 & 0xC0) != 0x80) {
                        throw new JUTFDataFormatException();
                    }
                    sbuf->append((jchar) (((b1 & 0x0F) << 12) |  ((b2 & 0x3F) << 6) | ((b3 & 0x3F) << 0)));
                    return 3;

                default:   // 10xx xxxx, 1111 xxxx
                    throw new JUTFDataFormatException();
            }
        }

        JBlockDataInputStream::~JBlockDataInputStream() {
        }
    }
}
