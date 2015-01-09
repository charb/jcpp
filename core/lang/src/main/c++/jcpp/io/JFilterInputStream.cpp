#include "jcpp/io/JFilterInputStream.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/io/JEOFException.h"

namespace jcpp{
    namespace io{

        JFilterInputStream::JFilterInputStream(JInputStream* in,jcpp::lang::JClass* _class):JInputStream(_class){
            this->in=in;
        }

        jint JFilterInputStream::read(){
            return in->read();
        }

        jint JFilterInputStream::read(JPrimitiveByteArray* b) {
            return read(b,0,b->size());
        }

        jint JFilterInputStream::read(JPrimitiveByteArray* b, jint off, jint len) {
            return in->read(b,off,len);
        }

        jlong JFilterInputStream::skip(jlong n){
            return in->skip(n);
        }

        void JFilterInputStream::mark(jint m){
            in->mark(m);
        }

        jint JFilterInputStream::available(){
            return in->available();
        }

        void JFilterInputStream::reset(){
            in->reset();
        }

        jbool JFilterInputStream::markSupported(){
            return in->markSupported();
        }

        void JFilterInputStream::close(){
            in->close();
        }

        JFilterInputStream::~JFilterInputStream() {
        }
    }
}
