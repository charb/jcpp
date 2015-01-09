#include "jcpp/io/JStringBufferInputStream.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

        JStringBufferInputStream::JStringBufferInputStream(JString* s):JInputStream(getClazz()){
            this->buffer=s;
            this->count=s->length();
            this->pos=0;
        }

        jint JStringBufferInputStream::read(){
            synchronized(this,{ 
                jint i=(pos < count) ? (buffer->charAt(pos++) & 0xFF) : -1;
                return i;
            })
        }

        jint JStringBufferInputStream::read(JPrimitiveByteArray* b, jint off, jint len){
            synchronized(this,{
                if (pos >= count) {
                    return -1;
                }
                if (pos + len > count) {
                    len = count - pos;
                }
                if (len <= 0) {
                    return 0;
                }
                JString* s = buffer;
                jint cnt = len;
                while (--cnt >= 0) {
                    b->setByte(off++,(jbyte)s->charAt(pos++));
                }
                return len;
            })
        }

        jlong JStringBufferInputStream::skip(jlong n){
            synchronized(this,{
                if (n < 0) {
                    return 0;
                }
                if (n > count - pos) {
                    n = count - pos;
                }
                pos += n;
                return n;
            })
        }

        jint JStringBufferInputStream::available(){
            synchronized(this,{
                jint i=count - pos;
                return i;
            })
        }

        void JStringBufferInputStream::reset(){
            synchronized(this,{
                pos=0;
            })
        }

        JStringBufferInputStream::~JStringBufferInputStream(){
        }
    }
}
