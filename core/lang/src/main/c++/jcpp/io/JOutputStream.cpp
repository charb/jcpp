#include "jcpp/io/JOutputStream.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JNullPointerException.h"

namespace jcpp{
    namespace io{

        JOutputStream::JOutputStream():JObject(getClazz()){
        }

        JOutputStream::JOutputStream(jcpp::lang::JClass* _class):JObject(_class){
        }
        
        void JOutputStream::write(JPrimitiveByteArray* b){
            write(b, 0, b->size());
        }

        void JOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            if (b == 0) {
                throw new JNullPointerException();
            } else {
                jint length = len;
                if ((off < 0) || (off > length) || (len < 0) || ((off + len) > length) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return;
                }
                for (jint i = 0 ; i < len ; i++) {
                    write(b->getByte(off + i));
                }
            }
        }

        void JOutputStream::flush(){
        }

        void JOutputStream::close(){
        }

        JOutputStream::~JOutputStream(){
        }
    }
}
