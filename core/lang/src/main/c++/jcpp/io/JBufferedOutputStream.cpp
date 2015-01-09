#include "jcpp/io/JBufferedOutputStream.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{


        JBufferedOutputStream::JBufferedOutputStream(JOutputStream* out,jint size):JFilterOutputStream(out,getClazz()){
            count=0;
            buf=new JPrimitiveByteArray(size);
        }

        void JBufferedOutputStream::flushBuffer(){
            if (count > 0) {
                out->write(buf, 0, count);
                count = 0;
            }
        }

        void JBufferedOutputStream::write(jint b){
            synchronized(this,{
                if (count >= buf->size()) {
                    flushBuffer();
                }
                buf->setByte(count++,((jbyte)b));
            })
        }

        void JBufferedOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            synchronized(this,{
                if (len >= buf->size()) {
                    flushBuffer();
                    out->write(b, off, len);
                    return;
                }
                if (len > buf->size() - count) {
                    flushBuffer();
                }
                JSystem::arraycopy(b, off, buf, count, len);
                count += len;
            })
        }

        void JBufferedOutputStream::flush(){
            synchronized(this,{
                flushBuffer();
                out->flush();
            })
        }

        JBufferedOutputStream::~JBufferedOutputStream() {
        }
    }
}


