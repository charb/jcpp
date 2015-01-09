#include "jcpp/io/JWriter.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

        JWriter::JWriter(jcpp::lang::JClass* _class):JObject(_class){
            writeBuffer=new JPrimitiveCharArray(1024);
            lock=this;
        }

        JWriter::JWriter(jcpp::lang::JClass* _class,JObject* lock):JObject(_class){
            writeBuffer=new JPrimitiveCharArray(1024);
            this->lock=lock;
        }

        void JWriter::write(jint c){
            synchronized(lock,{
                writeBuffer->setChar(0,(jchar)c);
                write(writeBuffer,0,1);
            })
        }

        void JWriter::write(JPrimitiveCharArray* cbuf) {
            write(cbuf, 0, cbuf->size());
        }

        void JWriter::write(JString* str){
            write(str,0,str->length());
        }

        void JWriter::write(JString* str,jint off,jint len){
            synchronized(lock,{
                JPrimitiveCharArray* cbuf;
                if (len <= 1024) {
                   cbuf = writeBuffer;
                } else {
                   cbuf = new JPrimitiveCharArray(len);
                }
                str->getChars(off, (off + len), cbuf, 0);
                write(cbuf, 0, len);
            })
        }

        JWriter* JWriter::append(JCharSequence* csq){
            if (csq==null){
                write(JString::NULL_STRING);
            }else{
                write(csq->toString());
            }
            return this;
        }

        JWriter* JWriter::append(JCharSequence* csq, jint start, jint end){
            JCharSequence* cs = (csq==null ? dynamic_cast<JCharSequence*>(JString::NULL_STRING) : csq);
            write(cs->subSequence(start,end)->toString());
            return this;
        }

        JWriter* JWriter::append(jchar c){
            write(c);
            return this;
        }

        JWriter::~JWriter(){
        }
    }
}
