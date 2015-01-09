#include "jcpp/io/JPipedInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/io/JPipedOutputStream.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JPipedInputStream::JPipedInputStream(JPipedOutputStream* src,jint pipeSize):JInputStream(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=null;
            in=-1;
            out=0;
            initPipe(pipeSize);
            connect(src);
        }

        JPipedInputStream::JPipedInputStream(jint pipeSize):JInputStream(getClazz()){
            closedByWriter=false;
            closedByReader=false;
            connected=false;
            buffer=null;
            in=-1;
            out=0;
            initPipe(pipeSize);
        }

        void JPipedInputStream::initPipe(jint pipeSize){
            if (pipeSize <= 0) {
                throw new JIllegalArgumentException(new JString("Pipe Size <= 0"));
            }
            buffer = new JPrimitiveByteArray(pipeSize);
        }

        void JPipedInputStream::connect(JPipedOutputStream* src){
            src->connect(this);
        }

        void JPipedInputStream::receive(jint b){
            synchronized(this,{
                checkStateForReceive();
                if (in == out){
                    awaitSpace();
                }
                if (in < 0) {
                    in = 0;
                    out = 0;
                }
                buffer->setByte(in++,(jbyte)(b & 0xFF));
                if (in >= buffer->size()) {
                    in = 0;
                }
            })
        }

        void JPipedInputStream::receive(JPrimitiveByteArray* b,jint off,jint len){
            synchronized(this,{
                checkStateForReceive();
                jint bytesToTransfer = len;
                while (bytesToTransfer > 0) {
                    if (in == out){
                        awaitSpace();
                    }
                    jint nextTransferAmount = 0;
                    if (out < in) {
                        nextTransferAmount = buffer->size() - in;
                    } else if (in < out) {
                        if (in == -1) {
                            in = out = 0;
                            nextTransferAmount = buffer->size() - in;
                        } else {
                            nextTransferAmount = out - in;
                        }
                    }
                    if (nextTransferAmount > bytesToTransfer){
                        nextTransferAmount = bytesToTransfer;
                    }
                    JSystem::arraycopy(b, off, buffer, in, nextTransferAmount);
                    bytesToTransfer -= nextTransferAmount;
                    off += nextTransferAmount;
                    in += nextTransferAmount;
                    if (in >= buffer->size()) {
                        in = 0;
                    }
                }
            })
        }

        void JPipedInputStream::checkStateForReceive(){
            if (!connected) {
                throw new JIOException(new JString("Pipe not connected"));
            } else if (closedByWriter || closedByReader) {
                throw new JIOException(new JString("Pipe closed"));
            }
        }

        void JPipedInputStream::awaitSpace(){
            while (in == out) {
                checkStateForReceive();
                notifyAll();
                wait(1000);
            }
        }

        void JPipedInputStream::receivedLast(){
            synchronized(this,{
                closedByWriter = true;
                notifyAll();
            })
        }

        jint JPipedInputStream::read(){
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
                jint ret = buffer->getByte(out++) & 0xFF;
                if (out >= buffer->size()) {
                    out = 0;
                }
                if (in == out) {
                    in = -1;
                }
                return ret;
            })
        }

        jint JPipedInputStream::read(JPrimitiveByteArray* b,jint off,jint len){
            synchronized(this,{
                if (b == null) {
                    throw new JNullPointerException();
                } else if (off < 0 || len < 0) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return 0;
                }
                jint c = read();
                if (c < 0) {
                    return -1;
                }
                b->setByte(off,(jbyte) c);
                jint rlen = 1;
                while ((in >= 0) && (len > 1)) {
                    jint available;
                    if (in > out) {
                        available = ((buffer->size() - out) < (in - out) ? buffer->size() - out : in-out);
                    } else {
                        available = buffer->size() - out;
                    }

                    if (available > (len - 1)) {
                        available = len - 1;
                    }
                    JSystem::arraycopy(buffer, out, b, off + rlen, available);
                    out += available;
                    rlen += available;
                    len -= available;
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

        jint JPipedInputStream::available(){
            synchronized(this,{
                jint i;
                if(in < 0){
                    i=0;
                }else if(in == out){
                    i=buffer->size();
                }else if (in > out){
                    i=in - out;
                }else{
                    i=in + buffer->size() - out;
                }
                return i;
            })
        }

        void JPipedInputStream::close(){
            synchronized(this,{
                closedByReader = true;
                in = -1;
            })
        }

        JPipedInputStream::~JPipedInputStream(){
        }
    }
}
