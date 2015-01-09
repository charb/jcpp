#include "jcpp/io/JPipedReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace io{

    	JPipedReader::JPipedReader(JPipedWriter* src, jint pipeSize):JReader(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=null;
            in=-1;
            out=0;
            initPipe(pipeSize);
            connect(src);
        }

        JPipedReader::JPipedReader(jint pipeSize):JReader(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=null;
            length=0;
            in=-1;
            out=0;
            initPipe(pipeSize);
        }

        void JPipedReader::initPipe(jint pipeSize){
            if (pipeSize <= 0) {
                throw new JIllegalArgumentException(new JString("Pipe size <= 0"));
            }
            buffer = new JPrimitiveCharArray(pipeSize);
        }

        void  JPipedReader::connect(JPipedWriter* src){
            src->connect(this);
        }

        void JPipedReader::receive(jint c){
            synchronized(this,{
                if (!connected){
                    throw new JIOException(new JString("Pipe not connected"));
                }else if (closedByWriter || closedByReader){
                    throw new JIOException(new JString("Pipe closed"));
                }

                while (in == out) {
                    notifyAll();
                    wait(1000);
                }
                if (in < 0) {
                    in = 0;
                    out = 0;
                }
                buffer->setChar(in++,(jchar) c);
                if (in >= buffer->size()) {
                    in = 0;
                }
            })
        }

        void JPipedReader::receive(JPrimitiveCharArray* c,jint off,jint len){
            synchronized(this,{
                while (--len >= 0) {
                    receive(c->getChar(off++));
                }
            })
        }

        void JPipedReader::receivedLast(){
            synchronized(this,{
                closedByWriter = true;
                notifyAll();
            })
        }

        jint JPipedReader::read(){
            synchronized(this,{
                if (!connected) {
                    throw new JIOException(new JString("Pipe not connected"));
                } else if (closedByReader) {
                    throw new JIOException(new JString("Pipe closed"));
                }

                while (in < 0) {
                    if (closedByWriter) {
                        return -1;
                    }
                    notifyAll();
                    wait(1000);
                }
                jint ret = buffer->getChar(out++);
                if (out >= buffer->size()) {
                    out = 0;
                }
                if (in == out) {
                    in = -1;
                }
                return ret;
            })
        }

        jint JPipedReader::read(JPrimitiveCharArray* cbuf, jint off, jint len){
            synchronized(this,{
                if (!connected) {
                    throw new JIOException(new JString("Pipe not connected"));
                } else if (closedByReader) {
                    throw new JIOException(new JString("Pipe closed"));
                }

                if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return 0;
                }

                jint c = read();
                if (c < 0) {
                    return -1;
                }
                cbuf->setChar(off,(jchar)c);
                jint rlen = 1;
                while ((in >= 0) && (--len > 0)) {
                    cbuf->setChar(off + rlen, buffer->getChar(out++));
                    rlen++;
                    if (out >= buffer->size()) {
                        out = 0;
                    }
                    if (in == out) {
                        in = -1;
                    }
                }
                return rlen;
            })
        }

        jbool JPipedReader::ready(){
            synchronized(this,{
                if (!connected) {
                    throw new JIOException(new JString("Pipe not connected"));
                } else if (closedByReader) {
                    throw new JIOException(new JString("Pipe closed"));
                }
                if (in < 0) {
                    return false;
                } else {
                    return true;
                }
            })
        }

        void JPipedReader::close(){
            synchronized(this,{
                in = -1;
                closedByReader = true;
            })
        }

        JPipedReader::~JPipedReader(){
        }
    }
}
