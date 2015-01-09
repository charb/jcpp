#include "jcpp/io/JFilterOutputStream.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JNullPointerException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JFilterOutputStream::JFilterOutputStream(JOutputStream* out,jcpp::lang::JClass* _class):JOutputStream(_class){
            this->out=out;
        }

        void JFilterOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            for (jint i=0;i<len;i++){
                out->write(b->getByte(off+i));
            }
        }

        void JFilterOutputStream::write(JPrimitiveByteArray* b){
            write(b,0,b->size());
        }

        void JFilterOutputStream::write(jint b){
            out->write(b);
        }

        void JFilterOutputStream::flush(){
            out->flush();
        }

        void JFilterOutputStream::close(){
            out->close();
        }

        JFilterOutputStream::~JFilterOutputStream(){
        }
    }
}

