#include "jcpp/io/JStringWriter.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JStringWriter::JStringWriter():JWriter(getClazz()){
            this->buf=new JStringBuffer();
            this->lock=buf;
        }

        void JStringWriter::write(jint c){
            buf->append((jint)c);
        }

        void JStringWriter::write(JPrimitiveCharArray* buf,jint off,jint len){
            this->buf->append(buf,off,len);
        }

        void JStringWriter::write(JString* str){
            buf->append((JString*)str);
        }

        void JStringWriter::write(JString* str,jint off,jint len){
            buf->append(dynamic_cast<JCharSequence*>(str),off,len);
        }

        JStringWriter* JStringWriter::append(JCharSequence* csq){
            if (csq==null){
                write(JString::NULL_STRING);
            }else{
                write(csq->toString());
            }
            return this;
        }

        JStringWriter* JStringWriter::append(JCharSequence* csq,jint start,jint end){
            buf->append(csq,start,end);
            return this;
        }

        JStringWriter* JStringWriter::append(jchar c){
            buf->append((jchar)c);
            return this;
        }

        JString* JStringWriter::toString(){
            return buf->toString();
        }

        JStringBuffer* JStringWriter::getBuffer(){
            return buf;
        }

        void JStringWriter::flush(){
        }

        void JStringWriter::close(){
        }

        JStringWriter::~JStringWriter(){
        }
    }
}
