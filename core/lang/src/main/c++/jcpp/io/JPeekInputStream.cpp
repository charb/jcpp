#include "jcpp/io/JPeekInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JEOFException.h"
#include "jcpp/io/JObjectInputStream.h"

namespace jcpp{
    namespace io{

        JPeekInputStream::JPeekInputStream(JInputStream* in):JInputStream(getClazz()){
            this->in=in;
            peekb=-1;
        }

        jint JPeekInputStream::peek(){
            return (peekb >= 0) ? peekb : (peekb = in->read());
        }

        jint JPeekInputStream::read(){
            if (peekb >= 0) {
                jint v = peekb;
                peekb = -1;
                return v;
            } else {
                return in->read();
            }
        }

        jint JPeekInputStream::read(JPrimitiveByteArray* b, jint off, jint len) {
            if (len == 0) {
                return 0;
            } else if (peekb < 0) {
                return in->read(b, off, len);
            } else {
                b->setByte(off++,(jbyte) peekb);
                len--;
                peekb = -1;
                jint n = in->read(b, off, len);
                return (n >= 0) ? (n + 1) : 1;
            }
        }

        void JPeekInputStream::readFully(JPrimitiveByteArray* b, jint off, jint len){
            jint n = 0;
            while (n < len) {
                jint count = read(b, off + n, len - n);
                if (count < 0) {
                    throw new JEOFException();
                }
                n += count;
            }
        }

        jlong JPeekInputStream::skip(jlong n){
            if (n <= 0) {
                return 0;
            }
            jint skipped = 0;
            if (peekb >= 0) {
                peekb = -1;
                skipped++;
                n--;
            }
            return skipped + skip(n);
        }

        jint JPeekInputStream::available(){
            return in->available() + ((peekb >= 0) ? 1 : 0);
        }

        void JPeekInputStream::close() {
            in->close();
        }

        JPeekInputStream::~JPeekInputStream() {
        }
    }
}

