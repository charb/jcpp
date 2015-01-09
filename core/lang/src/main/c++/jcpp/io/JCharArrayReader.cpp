#include "jcpp/io/JCharArrayReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace io{

        JCharArrayReader::JCharArrayReader(JPrimitiveCharArray* buf):JReader(getClazz()){
            this->buf = buf;
            this->pos = 0;
            this->count = buf->size();
            this->markedPos = 0;
        }

        JCharArrayReader::JCharArrayReader(JPrimitiveCharArray* buf,jint pos,jint length):JReader(getClazz()){
            this->buf = buf;
            this->pos = pos;
            this->count = (pos + length < buf->size() ? pos+length : buf->size());
            this->markedPos = pos;
        }

        void JCharArrayReader::ensureOpen(){
            synchronized(lock,{
                if (buf == null){
                    throw new JIOException(new JString("Stream closed"));
                }
            })
        }

        jint JCharArrayReader::read(){
            synchronized(lock,{
                ensureOpen();
                jint i;
                if (pos >= count){
                    i=-1;
                }else{
                    i=buf->getChar(pos++);
                }
                return i;
            })
        }

        jint JCharArrayReader::read(JPrimitiveCharArray* b, jint off, jint len){
            synchronized(lock,{
                ensureOpen();
                if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return 0;
                }

                if (pos >= count) {
                    return -1;
                }
                if (pos + len > count) {
                    len = count - pos;
                }
                if (len <= 0) {
                    return 0;
                }
                JSystem::arraycopy(buf, pos, b, off, len);
                pos += len;
                return len;
            })
        }

        jlong JCharArrayReader::skip(jlong n){
            synchronized(lock,{
                ensureOpen();
                if (pos + n > count) {
                    n = count - pos;
                }
                if (n < 0) {
                    return 0;
                }
                pos += n;
                return n;
            })
        }

        jbool JCharArrayReader::ready(){
            synchronized(lock,{
                ensureOpen();
                jbool b=(count - pos) > 0;
                return b;
            })
        }

        jbool JCharArrayReader::markSupported(){
            return true;
        }

        void JCharArrayReader::mark(jint){
            synchronized(lock,{
                ensureOpen();
                markedPos = pos;
            })
        }

        void JCharArrayReader::reset(){
            synchronized(lock,{
                ensureOpen();
                pos = markedPos;
            })
        }

        void JCharArrayReader::close(){
            buf=null;
        }

        JCharArrayReader::~JCharArrayReader(){
        }
    }
}
