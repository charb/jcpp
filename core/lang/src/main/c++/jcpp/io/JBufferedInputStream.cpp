#include "jcpp/io/JBufferedInputStream.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{

        JBufferedInputStream::JBufferedInputStream(JInputStream* in,jint size):JFilterInputStream(in,getClazz()){
            count=0;
            pos=0;
            markpos=-1;
            marklimit=0;
            buf=new JPrimitiveByteArray(size);
        }

        JInputStream* JBufferedInputStream::getInIfOpen(){
            JInputStream* input = in;
            if (input == null){
                throw new JIOException(new JString("Stream closed"));
            }
            return input;
        }

        JPrimitiveByteArray* JBufferedInputStream::getBufIfOpen(){
            JPrimitiveByteArray* buffer = buf;
             if (buffer == null){
                 throw new JIOException(new JString("Stream closed"));
             }
             return buffer;
        }

        void JBufferedInputStream::fill(){
            JPrimitiveByteArray* buffer = getBufIfOpen();
            if (markpos < 0){
                pos = 0;
            }else if (pos >= buffer->size()){
                if (markpos > 0) {
                    jint sz = pos - markpos;
                    JSystem::arraycopy(buffer, markpos, buffer, 0, sz);
                    pos = sz;
                    markpos = 0;
                } else if (buffer->size() >= marklimit) {
                    markpos = -1;
                    pos = 0;
                } else {
                    jint nsz = pos * 2;
                    if (nsz > marklimit){
                        nsz = marklimit;
                    }
                    JPrimitiveByteArray* nbuf = new JPrimitiveByteArray(nsz);
                    JSystem::arraycopy(buffer, 0, nbuf, 0, pos);
                    buffer = nbuf;
                }
                count = pos;
                jint n = getInIfOpen()->read(buffer, 0, buffer->size() - pos);
                if (n > 0){
                    count = n + pos;
                }
            }
        }

        jint JBufferedInputStream::read(){
            synchronized(this,{
                if (pos >= count) {
                    fill();
                    if (pos >= count){
                        return -1;
                    }
                }
                return getBufIfOpen()->getByte(pos++) & 0xff;
            })
        }

        jint JBufferedInputStream::read1(JPrimitiveByteArray* b, jint off, jint len){
            jint avail = count - pos;
            if (avail <= 0) {
                if (len >= getBufIfOpen()->size() && markpos < 0) {
                    return getInIfOpen()->read(b, off, len);
                }
                fill();
                avail = count - pos;
                if (avail <= 0){
                    return -1;
                }
            }
            jint cnt = (avail < len) ? avail : len;
            JSystem::arraycopy(getBufIfOpen(), pos, b, off, cnt);
            pos += cnt;
            return cnt;
        }

        jint JBufferedInputStream::read(JPrimitiveByteArray* b, jint off, jint len){
            synchronized(this,{
                getBufIfOpen();
                if (len == 0) {
                    return 0;
                }
                jint n = 0;
                for (;;) {
                    jint nread = read1(b, off + n, len - n);
                    if (nread <= 0){
                        return (n == 0) ? nread : n;
                    }
                    n += nread;
                    if (n >= len){
                        return n;
                    }
                    JInputStream* input = in;
                    if (input != null && input->available() <= 0){
                        return n;
                    }
                }
            })
        }

        jlong JBufferedInputStream::skip(jlong n){
            synchronized(this,{
                getBufIfOpen();
                if (n <= 0) {
                    return 0;
                }
                jlong avail = count - pos;
                if (avail <= 0) {
                    if (markpos <0) {
                        return getInIfOpen()->skip(n);
                    }
                    fill();
                    avail = count - pos;
                    if (avail <= 0){
                        return 0;
                    }
                }
                jlong skipped = (avail < n) ? avail : n;
                pos += skipped;
                return skipped;
            })
        }

        jint JBufferedInputStream::available(){
            synchronized(this,{
                jint n = count - pos;
                jint avail = getInIfOpen()->available();
                return (n > (JInteger::MAX_VALUE - avail) ? JInteger::MAX_VALUE : n + avail);
            })
        }

        void JBufferedInputStream::mark(jint readlimit) {
            synchronized(this,{
                marklimit = readlimit;
                markpos = pos;
            })
        }

        void JBufferedInputStream::reset(){
            synchronized(this,{
                getBufIfOpen();
                if (markpos < 0){
                    throw new JIOException(new JString("Resetting to invalid mark"));
                }
                pos = markpos;
            })
        }

        jbool JBufferedInputStream::markSupported() {
            return true;
        }

        void JBufferedInputStream::close(){
            in->close();
        }

        JBufferedInputStream::~JBufferedInputStream() {
        }
    }
}

