#include "jcpp/io/JBlockDataOutputStream.h"
#include "jcpp/io/JBits.h"
#include "jcpp/io/JUTFDataFormatException.h"
#include "jcpp/io/JObjectStreamConstants.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/io/JDataOutputStream.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JBlockDataOutputStream::JBlockDataOutputStream(JOutputStream* out):JOutputStream(getClazz()){
            buf=new JPrimitiveByteArray(MAX_BLOCK_SIZE);
            hbuf=new JPrimitiveByteArray(MAX_HEADER_SIZE);
            cbuf=new JPrimitiveCharArray(CHAR_BUF_SIZE);
            blkmode = false;
            pos = 0;
            this->out=out;
            this->dout = new JDataOutputStream(this);
        }

        jbool JBlockDataOutputStream::setBlockDataMode(jbool mode){
            if (blkmode == mode) {
                return blkmode;
            }
            drain();
            blkmode = mode;
            return !blkmode;
        }

        jbool JBlockDataOutputStream::getBlockDataMode() {
            return blkmode;
        }

        void JBlockDataOutputStream::write(jint b){
            if (pos >= MAX_BLOCK_SIZE) {
                drain();
            }
            buf->setByte(pos++, (jbyte) b);
        }

        void JBlockDataOutputStream::write(JPrimitiveByteArray* b){
            write(b, 0, b->size());
        }

        void JBlockDataOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            write(b, off, len, false);
        }

        void JBlockDataOutputStream::flush(){
            drain();
            out->flush();
        }

        void JBlockDataOutputStream::close(){
            flush();
            out->close();
        }

        void JBlockDataOutputStream::write(JPrimitiveByteArray* b, jint off, jint len, jbool copy) {
            if (!(copy || blkmode)) {
                drain();
                out->write(b, off, len);
                return;
            }

            while (len > 0) {
                if (pos >= MAX_BLOCK_SIZE) {
                    drain();
                }
                if (len >= MAX_BLOCK_SIZE && !copy && pos == 0) {
                    writeBlockHeader(MAX_BLOCK_SIZE);
                    out->write(b, off, MAX_BLOCK_SIZE);
                    off += MAX_BLOCK_SIZE;
                    len -= MAX_BLOCK_SIZE;
                } else {
                    jint wlen = (len < MAX_BLOCK_SIZE - pos ? len : MAX_BLOCK_SIZE - pos);
                    JSystem::arraycopy(b, off, buf, pos, wlen);
                    pos += wlen;
                    off += wlen;
                    len -= wlen;
                }
            }
        }

        void JBlockDataOutputStream::drain(){
            if (pos == 0) {
                return;
            }
            if (blkmode) {
                writeBlockHeader(pos);
            }
            out->write(buf, 0, pos);
            pos = 0;
        }

        void JBlockDataOutputStream::writeBlockHeader(jint len){
            if (len <= 0xFF) {
                hbuf->setByte(0, JObjectStreamConstants::TC_BLOCKDATA);
                hbuf->setByte(1,(jbyte) len);
                out->write(hbuf, 0, 2);
            } else {
                hbuf->setByte(0, JObjectStreamConstants::TC_BLOCKDATALONG);
                JBits::putInt(hbuf, 1, len);
                out->write(hbuf, 0, 5);
            }
        }

        void JBlockDataOutputStream::writeBoolean(jbool v){
            if (pos >= MAX_BLOCK_SIZE) {
                drain();
            }
            JBits::putBoolean(buf, pos++, v);
        }

        void JBlockDataOutputStream::writeByte(jint v){
            if (pos >= MAX_BLOCK_SIZE) {
                drain();
            }
            buf->setByte(pos++, (jbyte) v);
        }

        void JBlockDataOutputStream::writeChar(jint v){
            if (pos + 2 <= MAX_BLOCK_SIZE) {
                JBits::putChar(buf, pos,v);
                pos += 2;
            } else {
                dout->writeChar(v);
            }
        }

        void JBlockDataOutputStream::writeShort(jint v){
            if (pos + 2 <= MAX_BLOCK_SIZE) {
                JBits::putShort(buf, pos, (jshort) v);
                pos += 2;
            } else {
                dout->writeShort(v);
            }
        }

        void JBlockDataOutputStream::writeInt(jint v){
            if (pos + 4  <= MAX_BLOCK_SIZE) {
                JBits::putInt(buf, pos, v);
                pos += 4;
            } else {
                dout->writeInt(v);
            }
        }

        void JBlockDataOutputStream::writeFloat(jfloat v){
            if (pos + 4 <= MAX_BLOCK_SIZE) {
                JBits::putFloat(buf, pos, v);
                pos += 4;
            } else {
                dout->writeFloat(v);
            }
        }

        void JBlockDataOutputStream::writeLong(jlong v){
            if (pos + 8 <= MAX_BLOCK_SIZE) {
                JBits::putLong(buf, pos, v);
                pos += 8;
            } else {
                dout->writeLong(v);
            }
        }

        void JBlockDataOutputStream::writeDouble(jdouble v){
            if (pos + 8 <= MAX_BLOCK_SIZE) {
                JBits::putDouble(buf, pos, v);
                pos += 8;
            } else {
                dout->writeDouble(v);
            }
        }

        void JBlockDataOutputStream::writeBytes(JString* s){
            jint endoff = s->length();
            jint cpos = 0;
            jint csize = 0;
            for (jint off = 0; off < endoff; ) {
                if (cpos >= csize) {
                    cpos = 0;
                    csize = (endoff - off) < CHAR_BUF_SIZE ? endoff - off : CHAR_BUF_SIZE;
                    s->getChars(off, off + csize, cbuf, 0);
                }
                if (pos >= MAX_BLOCK_SIZE) {
                    drain();
                }
                jint n = (csize - cpos) < (MAX_BLOCK_SIZE - pos) ? csize - cpos : MAX_BLOCK_SIZE - pos;
                jint stop = pos + n;
                while (pos < stop) {
                    buf->setByte(pos++, (jbyte) cbuf->getChar(cpos++));
                }
                off += n;
            }
        }

        void JBlockDataOutputStream::writeChars(JString* s){
            jint endoff = s->length();
            for (jint off = 0; off < endoff; ) {
                jint csize = (endoff - off) < CHAR_BUF_SIZE ? endoff - off : CHAR_BUF_SIZE;
                s->getChars(off, off + csize, cbuf, 0);
                writeChars(cbuf, 0, csize);
                off += csize;
            }
        }

        void JBlockDataOutputStream::writeUTF(JString* s){
            writeUTF(s, getUTFLength(s));
        }

        void JBlockDataOutputStream::writeBooleans(JPrimitiveBooleanArray* v, jint off, jint len){
            jint endoff = off + len;
            while (off < endoff) {
                if (pos >= MAX_BLOCK_SIZE) {
                    drain();
                }
                jint stop = endoff < off + (MAX_BLOCK_SIZE - pos) ? endoff : off + (MAX_BLOCK_SIZE - pos);
                while (off < stop) {
                    JBits::putBoolean(buf, pos++, v->getBoolean(off++));
                }
            }
        }

        void JBlockDataOutputStream::writeChars(JPrimitiveCharArray* v, jint off, jint len){
            jint limit = MAX_BLOCK_SIZE - 2;
            jint endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 1;
                    jint stop = endoff < off + avail ? endoff : off + avail;
                    while (off < stop) {
                        JBits::putChar(buf, pos, v->getChar(off++));
                        pos += 2;
                    }
                } else {
                    dout->writeChar(v->getChar(off++));
                }
            }
        }

        void JBlockDataOutputStream::writeShorts(JPrimitiveShortArray* v, jint off, jint len){
            jint limit = MAX_BLOCK_SIZE - 2;
            jint endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 1;
                    jint stop = endoff < off + avail ? endoff : off + avail;
                    while (off < stop) {
                        JBits::putShort(buf, pos, v->getShort(off++));
                        pos += 2;
                    }
                } else {
                    dout->writeShort(v->getShort(off++));
                }
            }
        }

        void JBlockDataOutputStream::writeInts(JPrimitiveIntArray* v, jint off, jint len){
            jint limit = MAX_BLOCK_SIZE - 4;
            jint endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 2;
                    jint stop = endoff < off + avail ? endoff : off + avail ;
                    while (off < stop) {
                        JBits::putInt(buf, pos, v->getInt(off++));
                        pos += 4;
                    }
                } else {
                    dout->writeInt(v->getInt(off++));
                }
            }
        }

        void JBlockDataOutputStream::writeFloats(JPrimitiveFloatArray* v, jint off, jint len){
            jint limit = MAX_BLOCK_SIZE - 4;
            jint endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 2;
                    jint stop = endoff < off + avail ? endoff : off+ avail ;
                    while (off < stop) {
                        JBits::putFloat(buf, pos, v->getFloat(off++));
                        pos += 4;
                    }
                } else {
                    dout->writeFloat(v->getFloat(off++));
                }
            }
        }

        void JBlockDataOutputStream::writeLongs(JPrimitiveLongArray* v, jint off, jint len){
            jint limit = MAX_BLOCK_SIZE - 8;
            jint endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 3;
                    jint stop = endoff < off + avail ? endoff : off + avail;
                    while (off < stop) {
                        JBits::putLong(buf, pos, v->getLong(off++));
                        pos += 8;
                    }
                } else {
                    dout->writeLong(v->getLong(off++));
                }
            }
        }

        void JBlockDataOutputStream::writeDoubles(JPrimitiveDoubleArray* v, jint off, jint len){
            jint limit = MAX_BLOCK_SIZE - 8;
            jint endoff = off + len;
            while (off < endoff) {
                if (pos <= limit) {
                    jint avail = (MAX_BLOCK_SIZE - pos) >> 3;
                    jint stop = endoff < off + avail ? endoff : off + avail;
                    while (off < stop) {
                        JBits::putDouble(buf, pos, v->getDouble(off++));
                        pos += 8;
                    }
                } else {
                    dout->writeDouble(v->getDouble(off++));
                }
            }
        }

        jlong JBlockDataOutputStream::getUTFLength(JString* s){
            jint len = s->length();
            jlong utflen = 0;
            for (jint off = 0; off < len; ) {
                jint csize = (len - off) < CHAR_BUF_SIZE ? (len - off) : CHAR_BUF_SIZE;
                s->getChars(off, off + csize, cbuf, 0);
                for (jint cpos = 0; cpos < csize; cpos++) {
                    jchar c = cbuf->getChar(cpos);
                    if (c >= 0x0001 && c <= 0x007F) {
                        utflen++;
                    } else if (c > 0x07FF) {
                        utflen += 3;
                    } else {
                        utflen += 2;
                    }
                }
                off += csize;
            }
            return utflen;
        }

        void JBlockDataOutputStream::writeUTF(JString* s, jlong utflen){
            if (utflen > 0xFFFFL) {
                throw new JUTFDataFormatException();
            }
            writeShort((jint) utflen);
            if (utflen == (jlong) s->length()) {
                writeBytes(s);
            } else {
                writeUTFBody(s);
            }
        }

        void JBlockDataOutputStream::writeLongUTF(JString* s){
            writeLongUTF(s, getUTFLength(s));
        }

        void JBlockDataOutputStream::writeLongUTF(JString* s, jlong utflen){
            writeLong(utflen);
            if (utflen == (jlong) s->length()) {
                writeBytes(s);
            } else {
                writeUTFBody(s);
            }
        }

        void JBlockDataOutputStream::writeUTFBody(JString* s){
            jint limit = MAX_BLOCK_SIZE - 3;
            jint len = s->length();
            for (jint off = 0; off < len; ) {
                jint csize = len - off < CHAR_BUF_SIZE ? len - off  : CHAR_BUF_SIZE;
                s->getChars(off, off + csize, cbuf, 0);
                for (jint cpos = 0; cpos < csize; cpos++) {
                    jchar c = cbuf->getChar(cpos);
                    if (pos <= limit) {
                        if (c <= 0x007F && c != 0) {
                            buf->setByte(pos++, (jbyte) c);
                        } else if (c > 0x07FF) {
                            buf->setByte(pos + 2, (jbyte) (0x80 | ((c >> 0) & 0x3F)));
                            buf->setByte(pos + 1, (jbyte) (0x80 | ((c >> 6) & 0x3F)));
                            buf->setByte(pos + 0, (jbyte) (0xE0 | ((c >> 12) & 0x0F)));
                            pos += 3;
                        } else {
                            buf->setByte(pos + 1, (jbyte) (0x80 | ((c >> 0) & 0x3F)));
                            buf->setByte(pos + 0, (jbyte) (0xC0 | ((c >> 6) & 0x1F)));
                            pos += 2;
                        }
                    } else { 
                        if (c <= 0x007F && c != 0) {
                            write(c);
                        } else if (c > 0x07FF) {
                            write(0xE0 | ((c >> 12) & 0x0F));
                            write(0x80 | ((c >> 6) & 0x3F));
                            write(0x80 | ((c >> 0) & 0x3F));
                        } else {
                            write(0xC0 | ((c >> 6) & 0x1F));
                            write(0x80 | ((c >> 0) & 0x3F));
                        }
                    }
                }
                off += csize;
            }
        }

        JBlockDataOutputStream::~JBlockDataOutputStream(){
        }
    }
}
