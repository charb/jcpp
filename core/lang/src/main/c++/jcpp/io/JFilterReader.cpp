#include "jcpp/io/JFilterReader.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

        JFilterReader::JFilterReader(jcpp::lang::JClass* _class,JReader* in):JReader(_class,in){
            this->in=in;
        }

        jint JFilterReader::read(){
            return in->read();
        }

        jint JFilterReader::read(JPrimitiveCharArray* cbuf, jint off, jint len){
            return in->read(cbuf,off,len);
        }

        jlong JFilterReader::skip(jlong n){
            return in->skip(n);
        }

        jbool JFilterReader::ready(){
            return in->ready();
        }

        jbool JFilterReader::markSupported(){
            return in->markSupported();
        }

        void  JFilterReader::mark(jint m){
            in->mark(m);
        }

        void  JFilterReader::reset(){
            in->reset();
        }

        void  JFilterReader::close(){
            in->close();
        }

        JFilterReader::~JFilterReader(){
        }
    }
}
