#include "jcpp/io/JByteArrayInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace io{

        JByteArrayInputStream::JByteArrayInputStream(JPrimitiveByteArray* buf,jint offset,jint l):JInputStream(getClazz()){
            this->buf=buf;
            this->pos=offset;
            this->count=(offset+l < buf->size() ? offset+l : buf->size());
            imark=offset;
        }

        JByteArrayInputStream::JByteArrayInputStream(JPrimitiveByteArray* buf):JInputStream(getClazz()){
            this->buf=buf;
            this->pos=0;
            this->count=buf->size();
            imark=0;
        }

        jint JByteArrayInputStream::read(){
            synchronized(this,{
                return (pos < count) ? (buf->getByte(pos++) & 0xff) : -1;
            })
        }

        jint JByteArrayInputStream::read(JPrimitiveByteArray* b, jint off, jint len){
            synchronized(this,{
                if (b == null) {
                    throw new JNullPointerException();
                } else if (off < 0 || len < 0) {
                    throw new JIndexOutOfBoundsException();
                }

                if (pos >= count) {
                    return -1;
                }

                jint avail = count - pos;
                if (len > avail) {
                    len = avail;
                }
                if (len <= 0) {
                    return 0;
                }
                JSystem::arraycopy(buf, pos, b, off, len);
                pos += len;
                return len;
            })
        }

        jlong JByteArrayInputStream::skip(jlong n){
            synchronized(this,{
                jlong k = count - pos;
                if (n < k) {
                    k = n < 0 ? 0 : n;
                }
                pos += k;
                return k;
            })
        }

        jint JByteArrayInputStream::available(){
            synchronized(this,{
                return count - pos;
            })
        }

        jbool JByteArrayInputStream::markSupported(){
            return true;
        }

        void JByteArrayInputStream::mark(jint){
            synchronized(this,{
                imark=pos;
            })
        }

        void JByteArrayInputStream::reset(){
            synchronized(this,{
                pos=imark;
            })
        }

        void JByteArrayInputStream::close(){
        }

        JByteArrayInputStream::~JByteArrayInputStream(){
        }
    }
}
