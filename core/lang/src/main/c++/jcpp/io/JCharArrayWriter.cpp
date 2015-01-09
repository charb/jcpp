#include "jcpp/io/JCharArrayWriter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace io{

        JCharArrayWriter::JCharArrayWriter(jint size):JWriter(getClazz()){
            buf=new JPrimitiveCharArray(size);
            count=0;
        }

        void JCharArrayWriter::write(jint c){
            synchronized(lock,{
                jint newcount = count + 1;
                if (newcount > buf->size()) {
                    jint ns =(buf->size() << 1 < newcount ? newcount : buf->size()<<1);
                    buf = JArrays::copyOf(buf, ns);
                }
                buf->setChar(count,(jchar)c);
                count = newcount;
            })
        }

        void JCharArrayWriter::write(JPrimitiveCharArray* c, jint off, jint len){
            if ((off < 0) || (off > c->size()) || (len < 0) || ((off + len) > c->size()) || ((off + len) < 0)) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return;
            }
            synchronized(lock,{
                jint newcount = count + len;
                if (newcount > buf->size()) {
                    jint ns =(buf->size() << 1 < newcount ? newcount : buf->size()<<1);
                    buf = JArrays::copyOf(buf, ns);
                }
                JSystem::arraycopy(c, off, buf, count, len);
                count = newcount;
            })
        }

        void JCharArrayWriter::write(JString* str, jint offset, jint len){
            synchronized(lock,{
                jint newcount = count + len;
                if (newcount > buf->size()) {
                    jint ns =(buf->size() << 1 < newcount ? newcount : buf->size()<<1);
                    buf = JArrays::copyOf(buf, ns);
                }
                str->getChars(offset, offset + len, buf, count);
                count = newcount;
            })
        }

        void JCharArrayWriter::writeTo(JWriter* out){
            synchronized(lock,{
                out->write(buf,0,count);
            })
        }

        JCharArrayWriter* JCharArrayWriter::append(JCharSequence* csq){
            JString* s = (csq == null ? JString::NULL_STRING : csq->toString());
            write(s, 0, s->length());
            return this;
        }

        JCharArrayWriter* JCharArrayWriter::append(JCharSequence* csq,jint start,jint end){
            JString* s = (csq == null ? JString::NULL_STRING : csq->toString());
            s=s->subSequence(start, end)->toString();
            write(s, 0, s->length());
            return this;
        }

        JCharArrayWriter* JCharArrayWriter::append(jchar c){
            write(c);
            return this;
        }

        void JCharArrayWriter::reset(){
            synchronized(lock,{
                count=0;
            })
        }

        JPrimitiveCharArray* JCharArrayWriter::toCharArray(){
            synchronized(lock,{
                return JArrays::copyOf(buf, count);
            })
        }

        jint JCharArrayWriter::size(){
            synchronized(lock,{
                return buf->size();
            })
        }

        JString* JCharArrayWriter::toString(){
            synchronized(lock,{
                return new JString(buf, 0, count);
            })
        }

        void JCharArrayWriter::flush(){
        }

        void JCharArrayWriter::close(){
        }

        JCharArrayWriter::~JCharArrayWriter(){
        }
    }
}
