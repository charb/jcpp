#include "jcpp/io/JSequenceInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace io{

        JSequenceInputStream::JSequenceInputStream(JEnumeration* e):JInputStream(getClazz()){
            this->e=e;
            nextStream();
        }

        JSequenceInputStream::JSequenceInputStream(JInputStream* s1,JInputStream* s2){
            vec=new JVector();
            vec->addElement(s1);
            vec->addElement(s2);
            e=vec->elements();
            nextStream();
        }

        void JSequenceInputStream::nextStream(){
            if (in != null) {
                in->close();
            }
            if (e->hasMoreElements()) {
                in = (JInputStream*) e->nextElement();
                if (in == null){
                    throw new JNullPointerException();
                }
            }else{
                in = null;
            }
        }

        void  JSequenceInputStream::close(){
            do {
                nextStream();
            } while (in != null);
        }

        jint JSequenceInputStream::read(JPrimitiveByteArray* b, jint off, jint len){
            if (in == null) {
                return -1;
            } else if (b == null) {
                throw new JNullPointerException();
            } else if (off < 0 || len < 0 ) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return 0;
            }
            jint n = in->read(b, off, len);
            if (n <= 0) {
                nextStream();
                return read(b, off, len);
            }
            return n;
        }

        jint JSequenceInputStream::read(){
            if (in == null) {
                return -1;
            }
            jint c = in->read();
            if (c == -1) {
                nextStream();
                return read();
            }
            return c;
        }

        jint JSequenceInputStream::available(){
            if(in == null) {
                return 0;
            }
            return in->available();
        }

        JSequenceInputStream::~JSequenceInputStream(){
        }
    }
}
