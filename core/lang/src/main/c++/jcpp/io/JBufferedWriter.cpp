#include "jcpp/io/JBufferedWriter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::lang;
using jcpp::native::api::NativeFactory;

namespace jcpp{
    namespace io{

        JBufferedWriter::JBufferedWriter(JWriter* out,jint size):JWriter(getClazz(),out){
            this->out=out;
            this->cb=new JPrimitiveCharArray(size);
            nChars=size;
            nextChar=0;
        }

        void JBufferedWriter::ensureOpen(){
            synchronized(lock,{
                if (out==null){
                    throw new JIOException(new JString("stream closed"));
                }
            })
        }

        void JBufferedWriter::flushBuffer(){
            synchronized(lock,{
                ensureOpen();
                if (nextChar==0){
                    return;
                }
                out->write(cb, 0, nextChar);
                nextChar = 0;
            })
        }

        void JBufferedWriter::write(jint c){
            synchronized(lock,{
                ensureOpen();
                if (nextChar >= nChars){
                    flushBuffer();
                }
                cb->setChar(nextChar++,(jchar) c);
            })
        }

        void JBufferedWriter::write(JPrimitiveCharArray* c){
            return JWriter::write(c);
        }

        void JBufferedWriter::write(JPrimitiveCharArray* cbuf, jint off, jint len){
            synchronized(lock,{
                ensureOpen();
                if (len==0){
                    return;
                }
                if (len >= nChars) {
                    flushBuffer();
                    out->write(cbuf, off, len);
                }else{
                    jint b = off;
                    jint t = off + len;
                    while (b < t) {
                        jint d = (nChars - nextChar < t - b ? nChars - nextChar : t - b);
                        JSystem::arraycopy(cbuf, b, cb, nextChar, d);
                        b += d;
                        nextChar += d;
                        if (nextChar >= nChars){
                            flushBuffer();
                        }
                    }
                }
            })
        }

        void JBufferedWriter::write(JString* str){
            JWriter::write(str);
        }

        void JBufferedWriter::write(JString* str, jint off, jint len){
            synchronized(lock,{
                ensureOpen();
                jint b = off;
                jint t = off + len;
                while (b < t) {
                    jint d = (nChars - nextChar < t - b ? nChars - nextChar : t - b);
                    str->getChars(b, b + d, cb, nextChar);
                    b += d;
                    nextChar += d;
                    if (nextChar >= nChars){
                        flushBuffer();
                    }
                }
            })
        }

        void JBufferedWriter::newLine(){
            JWriter::write(JSystem::lineSeparator());
        }

        void JBufferedWriter::flush(){
            synchronized(lock,{
                flushBuffer();
                out->flush();
            })
        }

        void JBufferedWriter::close(){
            synchronized(lock,{
                if (out!=null){
                    flushBuffer();
                    out=null;
                    cb=null;
                }
            })
        }

        JBufferedWriter::~JBufferedWriter(){
        }
    }
}
