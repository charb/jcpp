#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JBits.h"
#include "jcpp/io/JUTFDataFormatException.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JDataOutputStream::JDataOutputStream():JFilterOutputStream(null,getClazz()){
            written=0;
            this->bytearr=null;
            writeBuffer=new JPrimitiveByteArray(8);
        }

        JDataOutputStream::JDataOutputStream(JOutputStream *out):JFilterOutputStream(out,getClazz()){
            written=0;
            this->bytearr=null;
            writeBuffer=new JPrimitiveByteArray(8);
        }

        void JDataOutputStream::incCount(jint value){
            jint temp = written + value;
            if (temp < 0) {
                temp = JInteger::MAX_VALUE;
            }
            written = temp;
        }

        void JDataOutputStream::write(jint b){
            synchronized(this,{
                out->write(b);
                incCount(1);
            })
        }

        void JDataOutputStream::write(JPrimitiveByteArray* b){
            JFilterOutputStream::write(b);
        }

        void JDataOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            synchronized(this,{
                out->write(b, off, len);
                incCount(len);
            })
        }

        void JDataOutputStream::flush(){
            out->flush();
        }

        void JDataOutputStream::close(){
            out->close();
        }

        void JDataOutputStream::writeBoolean(jbool v){
            write(v ? 1 : 0);
        }

        void JDataOutputStream::writeByte(jint v){
            write(v);
        }

        void JDataOutputStream::writeShort(jint v){
            write((jbyte)(v >> 8) & 0xFF);
            write((jbyte)(v >> 0) & 0xFF);
        }

        void JDataOutputStream::writeChar(jint v){
            write((jbyte)(v >> 8) & 0xFF);
            write((jbyte)(v >> 0) & 0xFF);
        }

        void JDataOutputStream::writeInt(jint v){
            write(((v >> 24) & 0xFF));
            write(((v >> 16) & 0xFF));
            write(((v >>  8) & 0xFF));
            write(((v >>  0) & 0xFF));
        }

        void JDataOutputStream::writeLong(jlong v){
            writeBuffer->setByte(0,(v >> 56));
            writeBuffer->setByte(1,(v >> 48));
            writeBuffer->setByte(2,(v >> 40));
            writeBuffer->setByte(3,(v >> 32));
            writeBuffer->setByte(4,(v >> 24));
            writeBuffer->setByte(5,(v >> 16));
            writeBuffer->setByte(6,(v >>  8));
            writeBuffer->setByte(7,(v >>  0));
            write(writeBuffer, 0, 8);
        }

        void JDataOutputStream::writeFloat(jfloat v){
            JBits::putFloat(writeBuffer, 0, v);
            write(writeBuffer,0,4);
        }

        void JDataOutputStream::writeDouble(jdouble v){
            JBits::putDouble(writeBuffer, 0, v);
            write(writeBuffer,0,8);
        }

        void JDataOutputStream::writeBytes(JString* s){
            jint len = s->length();
            for (jint i = 0 ; i < len ; i++) {
                write((jbyte)s->charAt(i));
            }
        }

        void JDataOutputStream::writeChars(JString* s){
            jint len = s->length();
            for (jint i = 0 ; i < len ; i++) {
                jint v = s->charAt(i);
                write((v >> 8) & 0xFF);
                write((v >> 0) & 0xFF);
            }
        }

        void JDataOutputStream::writeUTF(JString* str){
            writeUTF(str, this);
        }

        jint JDataOutputStream::writeUTF(JString* str, JDataOutput *out){
            jint strlen = str->length();
            jint utflen = 0;
            jint c, count = 0;

            for (jint i = 0; i < strlen; i++) {
                c = str->charAt(i);
                if ((c >= 0x0001) && (c <= 0x007F)) {
                    utflen++;
                } else if (c > 0x07FF) {
                    utflen += 3;
                } else {
                    utflen += 2;
                }
            }

            if (utflen > 65535){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("encoded String too long ")->append(utflen);
                throw new JUTFDataFormatException(builder->toString());
            }

            JDataOutputStream* dos = dynamic_cast<JDataOutputStream*>(out);
            if(dos->bytearr == null || (dos->bytearr->size() < (utflen+2))){
                jint l = (utflen*2) + 2;
                dos->bytearr = new JPrimitiveByteArray(l);
            }
            JPrimitiveByteArray* bytearr = dos->bytearr;

            bytearr->setByte(count++,(jbyte) ((utflen >> 8) & 0xFF));
            bytearr->setByte(count++,(jbyte) ((utflen >> 0) & 0xFF));

            jint i=0;
            for (i=0; i < strlen; i++) {
                c = str->charAt(i);
                if (!((c >= 0x0001) && (c <= 0x007F))){
                    break;
                }
                bytearr->setByte(count++,(jbyte) c);
            }
            for (;i < strlen; i++){
                c = str->charAt(i);
                if ((c >= 0x0001) && (c <= 0x007F)) {
                    bytearr->setByte(count++,(jbyte) c);

                } else if (c > 0x07FF) {
                    bytearr->setByte(count++,(jbyte) (0xE0 | ((c >> 12) & 0x0F)));
                    bytearr->setByte(count++,(jbyte) (0x80 | ((c >>  6) & 0x3F)));
                    bytearr->setByte(count++,(jbyte) (0x80 | ((c >>  0) & 0x3F)));
                } else {
                    bytearr->setByte(count++,(jbyte) (0xC0 | ((c >>  6) & 0x1F)));
                    bytearr->setByte(count++,(jbyte) (0x80 | ((c >>  0) & 0x3F)));
                }
            }
            write(bytearr, 0, utflen+2);
            return utflen + 2;

        }

        jint JDataOutputStream::size(){
            return written;
        }

        JDataOutputStream::~JDataOutputStream(){
        }
    }
}
