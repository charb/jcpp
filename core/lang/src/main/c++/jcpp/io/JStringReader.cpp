#include "jcpp/io/JStringReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace io{

        JStringReader::JStringReader(JString* str):JReader(getClazz()){
            this->str=str;
            this->length=str->length();
            next=0;
            imark=0;
        }

        jint JStringReader::read(){
            synchronized(lock,{
                if (next >= length){
                    return -1;
                }
                jint i=(jint)str->charAt(next++);
                return i;
            })
        }

        jint JStringReader::read(JPrimitiveCharArray* cbuf, jint off, jint len){
            synchronized(lock,{
                if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return 0;
                }
                if (next >= length){
                    return -1;
                }
                jint n = (length - next < len ? length-next : len);
                str->getChars(next, next + n, cbuf, off);
                next += n;
                return n;
            })
        }

        jlong JStringReader::skip(jlong ns){
            synchronized(lock,{
                if (next >= length){
                    return 0;
                }
                jlong n = (length - next < ns ? length-next : ns);
                n = (-next > n ? -next : n);
                next += n;
                return n;
            })
        }

        jbool JStringReader::ready(){
            return true;
        }

        jbool JStringReader::markSupported(){
            return true;
        }

        void JStringReader::mark(jint m){
            synchronized(lock,{
                if (m < 0){
                    throw new JIllegalArgumentException(new JString("Read-ahead limit < 0"));
                }
                imark = next;
            })
        }

        void JStringReader::reset(){
            synchronized(lock,{
                next = imark;
            })
        }

        void JStringReader::close(){
            str=null;
        }

        JStringReader::~JStringReader(){
        }
    }
}
