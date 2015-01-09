#include "jcpp/io/JFilterWriter.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

        JFilterWriter::JFilterWriter(jcpp::lang::JClass* _class,JWriter* out):JWriter(_class,out){
            this->out=out;
        }

        void JFilterWriter::write(jint c){
            out->write(c);
        }

        void  JFilterWriter::write(JPrimitiveCharArray* cbuf, jint off, jint len){
            out->write(cbuf,off,len);
        }

        void  JFilterWriter::write(JString* str, jint off, jint len){
            out->write(str,off,len);
        }

        void  JFilterWriter::flush(){
            out->flush();
        }

        void  JFilterWriter::close(){
            out->close();
        }

        JFilterWriter::~JFilterWriter(){
        }
    }
}
