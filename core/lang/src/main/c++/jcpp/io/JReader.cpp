#include "jcpp/io/JReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{

        JReader::JReader(jcpp::lang::JClass* _class):JObject(_class){
            lock=this;
            skipBuffer=null;
            readBuffer=new JPrimitiveCharArray(1);
            length=0;
        }

        JReader::JReader(jcpp::lang::JClass* _class,JObject* lock):JObject(_class){
            this->lock=lock;
            skipBuffer=null;
            readBuffer=new JPrimitiveCharArray(1);
            length=0;
        }

        jint JReader::read(){
            jint r;
            if (read(readBuffer, 0, 1) == -1){
                r=-1;
            }else{
                r=readBuffer->getChar(0);
            }
            return r;
        }

        jlong JReader::skip(jlong n){
            if (n < 0){
                throw new JIllegalArgumentException(new JString("skip value is negative"));
            }
            jint nn = (n < 8192 ? n : 8192);
            synchronized(lock,{
                if ((skipBuffer == null) || (length < nn)){
                    skipBuffer = new JPrimitiveCharArray(nn);
                    length=nn;
                }
                jlong r = n;
                while (r > 0) {
                    jint nc = read(skipBuffer, 0, (r < nn ? r : nn));
                    if (nc == -1){
                        break;
                    }
                    r -= nc;
                }
                return n - r;
            })
        }

        jbool JReader::ready(){
            return false;
        }

        jbool JReader::markSupported(){
            return false;
        }

        void  JReader::mark(jint){
            throw new JIOException(new JString("mark() not supported"));
        }

        void JReader::reset(){
            throw new JIOException(new JString("reset() not supported"));
        }

        JReader::~JReader(){
        }
    }
}
