#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/io/JEOFException.h"

using namespace jcpp::util;

namespace jcpp{
    namespace io{

    	JInputStream::JInputStream():JObject(getClazz()){
            this->skipBuffer=null;
        }

        JInputStream::JInputStream(jcpp::lang::JClass* _class):JObject(_class){
            this->skipBuffer=null;
        }

        jint JInputStream::read(JPrimitiveByteArray* b) {
            return read(b,0,b->size());
        }

        jint JInputStream::read(JPrimitiveByteArray* b, jint off, jint len) {
            if (b == null) {
                throw new JNullPointerException();
            }else if (len == 0) {
                return 0;
            }

            jint c = read();
            if (c == -1) {
                return -1;
            }
            b->setByte(off,(jbyte)c);

            jint i = 1;
            try {
                for (; i < len ; i++) {
                    c = read();
                    if (c == -1) {
                        break;
                    }
                    b->setByte(off + i,(jbyte)c);
                }
            } catch (JIOException* ee) {
            }
            return i;
        }

        jlong JInputStream::skip(jlong n){
            jlong remaining = n;
            jint nr;
            if (skipBuffer == null){
                skipBuffer = new JPrimitiveByteArray(SKIP_BUFFER_SIZE);
            }

            if (n <= 0) {
                return 0;
            }

            while (remaining > 0) {
                nr = read(skipBuffer, 0,(SKIP_BUFFER_SIZE<remaining ? SKIP_BUFFER_SIZE : remaining));
                if (nr < 0) {
                    break;
                }
                remaining -= nr;
            }

            return n - remaining;
        }

        void JInputStream::mark(jint){
        }

        void JInputStream::reset(){
            throw new JIOException(new JString("mark/reset not supported"));
        }

        jint JInputStream::available(){
            return 0;
        }

        void JInputStream::close(){
        }

        jbool JInputStream::markSupported(){
            return false;
        }

        JInputStream::~JInputStream() {
        }
    }
}
