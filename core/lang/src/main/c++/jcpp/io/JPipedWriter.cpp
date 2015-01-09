#include "jcpp/io/JPipedWriter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/io/JPipedReader.h"

namespace jcpp{
    namespace io{

    	JPipedWriter::JPipedWriter(JPipedReader* snk):JWriter(getClazz()){
            closed=false;
            connect(snk);
        }

        JPipedWriter::JPipedWriter():JWriter(getClazz()){
            closed=false;
        }

        void JPipedWriter::connect(JPipedReader* snk){
            synchronized(this,{
                if (snk == null) {
                    throw new JNullPointerException();
                } else if (sink != null || snk->connected) {
                    throw new JIOException(new JString("Already connected"));
                } else if (snk->closedByReader || closed) {
                    throw new JIOException(new JString("Pipe closed"));
                }

                this->sink = snk;
                snk->in = -1;
                snk->out = 0;
                snk->connected = true;
            })
        }

        void JPipedWriter::write(jint c){
            if (sink == null) {
                throw new JIOException(new JString("Pipe not connected"));
            }
            sink->receive(c);
        }

        void JPipedWriter::write(JPrimitiveCharArray* cbuf, jint off, jint len){
            if (sink == null) {
                throw new JIOException(new JString("Pipe not connected"));
            } else if (off | len | (off + len)) {
                throw new JIndexOutOfBoundsException();
            }
            sink->receive(cbuf, off, len);
        }

        void JPipedWriter::flush(){
            synchronized(this,{
                if (sink != null) {
                    if (sink->closedByReader || closed) {
                        throw new JIOException(new JString("Pipe closed"));
                    }
                    synchronized(sink,{
                        sink->notifyAll();
                    })
                }
            })
        }

        void JPipedWriter::close(){
            closed = true;
            if (sink != null) {
                sink->receivedLast();
            }
        }

        JPipedWriter::~JPipedWriter(){
        }
    }
}
