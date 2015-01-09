#include "jcpp/io/JPushbackReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace io{

        JPushbackReader::JPushbackReader(JReader* in,jint size):JFilterReader(getClazz(),in){
            if (size <= 0) {
                throw new JIllegalArgumentException(new JString("size <= 0"));
            }
            this->buf = new JPrimitiveCharArray(size);
            this->pos = size;
        }

        void JPushbackReader::ensureOpen(){
            if (buf == null){
                throw new JIOException(new JString("Stream closed"));
            }
        }

        jint JPushbackReader::read(){
            synchronized(lock,{
                ensureOpen();
                jint i;
                if (pos < buf->size()){
                    i=buf->getChar(pos++);
                }else{
                    i=JReader::read();
                }
                return i;
            })
        }

        jint JPushbackReader::read(JPrimitiveCharArray* cbuf, jint off, jint len){
            synchronized(lock,{
                ensureOpen();
                if (len <= 0) {
                    if (len < 0) {
                        throw new JIndexOutOfBoundsException();
                    } else if ((off < 0)) {
                        throw new JIndexOutOfBoundsException();
                    }
                    return 0;
                }
                jint avail = buf->size() - pos;
                if (avail > 0) {
                    if (len < avail){
                        avail = len;
                    }
                    JSystem::arraycopy(buf, pos, cbuf, off, avail);
                    pos += avail;
                    off += avail;
                    len -= avail;
                }
                if (len > 0) {
                    len = JFilterReader::read(cbuf, off, len);
                    if (len == -1) {
                        return (avail == 0) ? -1 : avail;
                    }
                    return avail + len;
                }
                return avail;
            })
        }

        void JPushbackReader::unread(jint c){
            synchronized(lock,{
                ensureOpen();
                if (pos == 0){
                    throw new JIOException(new JString("Pushback buffer overflow"));
                }
                buf->setChar(--pos,(jchar) c);
            })
        }

        void  JPushbackReader::unread(JPrimitiveCharArray* cbuf, jint off, jint len){
            synchronized(lock,{
                ensureOpen();
                if (len > pos){
                    throw new JIOException(new JString("Pushback buffer overflow"));
                }
                pos -= len;
                JSystem::arraycopy(cbuf, off, buf, pos, len);
            })
        }

        void  JPushbackReader::unread(JPrimitiveCharArray* cbuf){
            unread(cbuf,0,cbuf->size());
        }

        jbool JPushbackReader::ready(){
            synchronized(lock,{
                ensureOpen();
                jbool b=(pos < buf->size()) || JReader::ready();
                return b;
            })
        }

        void  JPushbackReader::mark(jint){
            throw new JIOException(new JString("mark/reset not supported"));
        }

        void  JPushbackReader::reset(){
            throw new JIOException(new JString("mark/reset not supported"));
        }

        jbool JPushbackReader::markSupported(){
            return false;
        }

        void  JPushbackReader::close(){
            JFilterReader::close();
            buf=null;
        }

        jlong JPushbackReader::skip(jlong n){
            synchronized(lock,{
                ensureOpen();
                jint avail = buf->size() - pos;
                if (avail > 0) {
                    if (n <= avail) {
                        pos += n;
                        return n;
                    } else {
                        pos = buf->size();
                        n -= avail;
                    }
                }
                jlong l=avail + JReader::skip(n);
                return l;
            })
        }

        JPushbackReader::~JPushbackReader(){
        }
    }
}
