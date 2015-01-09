#include "jcpp/io/JPushbackInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInteger.h"

namespace jcpp{
    namespace io{

        JPushbackInputStream::JPushbackInputStream(JInputStream* in,jint size):JFilterInputStream(in,getClazz()){
            if (size <= 0) {
                throw new JIllegalArgumentException(new JString("size <= 0"));
            }
            this->buf = new JPrimitiveByteArray(size);
            this->pos = size;
        }

        void JPushbackInputStream::ensureOpen(){
            if (in == null){
                throw new JIOException(new JString("Stream closed"));
            }
        }

        jint JPushbackInputStream::read(){
            ensureOpen();
            if (pos < buf->size()) {
                return buf->getByte(pos++) & 0xff;
            }
            return JFilterInputStream::read();
        }

        jint JPushbackInputStream::read(JPrimitiveByteArray* b, jint off, jint len){
            ensureOpen();
            if (b == null) {
                throw new JNullPointerException();
            } else if (off < 0 || len < 0) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }

            jint avail = buf->size() - pos;
            if (avail > 0) {
                if (len < avail) {
                    avail = len;
                }
                JSystem::arraycopy(buf, pos, b, off, avail);
                pos += avail;
                off += avail;
                len -= avail;
            }
            if (len > 0) {
                len = JFilterInputStream::read(b, off, len);
                if (len == -1) {
                    return avail == 0 ? -1 : avail;
                }
                return avail + len;
            }
            return avail;
        }

        void JPushbackInputStream::unread(jint b){
            ensureOpen();
            if (pos == 0) {
                throw new JIOException(new JString("Push back buffer is full"));
            }
            buf->setByte(--pos,(jbyte)b);
        }

        void JPushbackInputStream::unread(JPrimitiveByteArray* b,jint off,jint len){
            ensureOpen();
            if (len > pos) {
                throw new JIOException(new JString("Push back buffer is full"));
            }
            pos -= len;
            JSystem::arraycopy(b, off, buf, pos, len);
        }

        void JPushbackInputStream::unread(JPrimitiveByteArray* b){
            unread(b,0,b->size());
        }

        jint JPushbackInputStream::available(){
            ensureOpen();
            jint n = buf->size() - pos;
            jint avail = JFilterInputStream::available();
            return n > (JInteger::MAX_VALUE - avail) ? JInteger::MAX_VALUE : n + avail;
        }

        jlong JPushbackInputStream::skip(jlong n){
            ensureOpen();
            if (n <= 0) {
                return 0;
            }
            jlong pskip = buf->size() - pos;
            if (pskip > 0) {
                if (n < pskip) {
                    pskip = n;
                }
                pos += pskip;
                n -= pskip;
            }
            if (n > 0) {
                pskip += JFilterInputStream::skip(n);
            }
            return pskip;
        }

        jbool JPushbackInputStream::markSupported(){
            return false;
        }

        void JPushbackInputStream::mark(jint){
        }

        void JPushbackInputStream::reset(){
            throw new JIOException(new JString("mark/reset not supported"));
        }

        void JPushbackInputStream::close(){
            synchronized(this,{
                if (in == null){
                    return;
                }
                in->close();
                in = null;
                buf = null;
            })
        }

        JPushbackInputStream::~JPushbackInputStream(){
        }
    }
}
