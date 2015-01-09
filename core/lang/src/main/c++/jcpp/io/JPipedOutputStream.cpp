#include "jcpp/io/JPipedOutputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace io{

        JPipedOutputStream::JPipedOutputStream(JPipedInputStream* sink):JOutputStream(getClazz()){
            this->sink=sink;
        }

        JPipedOutputStream::JPipedOutputStream():JOutputStream(getClazz()){
            this->sink=null;
        }

        void JPipedOutputStream::connect(JPipedInputStream* sink){
            synchronized(this,{
                if (sink == null) {
                    throw new JNullPointerException();
                } else if (sink != null || sink->connected) {
                    throw new JIOException(new JString("Already connected"));
                }
                this->sink = sink;
                this->sink->in = -1;
                this->sink->out = 0;
                this->sink->connected = true;
            })
        }

        void JPipedOutputStream::write(jint b){
            if (sink == null) {
                throw new JIOException(new JString("Pipe not connected"));
            }
            sink->receive(b);
        }

        void JPipedOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            if (sink == null) {
                throw new JIOException(new JString("Pipe not connected"));
            } else if (b == NULL) {
                throw new JNullPointerException();
            } else if ((off < 0) || (len < 0)) {
                throw new JIndexOutOfBoundsException();
            } else if (len == 0) {
                return;
            }
            sink->receive(b, off, len);
        }

        void JPipedOutputStream::flush(){
            synchronized(this,{
                if (sink != NULL) {
                    sink->notifyAll();
                }
            })
        }

        void JPipedOutputStream::close(){
            if (sink != NULL) {
                sink->receivedLast();
            }
        }

        JPipedOutputStream::~JPipedOutputStream(){
        }
    }
}
