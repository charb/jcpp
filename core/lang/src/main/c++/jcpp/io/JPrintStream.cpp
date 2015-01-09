#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/io/JFileOutputStream.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JPrintStream::JPrintStream(JOutputStream* out, JString *encoding, jbool autoFlush):JFilterOutputStream(null,getClazz()){
        	this->out=out;
            this->autoFlush=autoFlush;
            this->trouble=false;
            this->closing=false;
            this->charOut=new JOutputStreamWriter(this, encoding);
            this->textOut=new JBufferedWriter(charOut);
        }

        JPrintStream::JPrintStream(JString* fileName, JString *encoding, jbool autoFlush):JFilterOutputStream(null,getClazz()){
            this->out=new JFileOutputStream(fileName);
            this->autoFlush=autoFlush;
            this->trouble=false;
            this->closing=false;
            this->charOut=new JOutputStreamWriter(this, encoding);
            this->textOut=new JBufferedWriter(charOut);
        }

        JPrintStream::JPrintStream(JFile* file, JString *encoding, jbool autoFlush):JFilterOutputStream(null,getClazz()){
            this->out=new JFileOutputStream(file);
            this->autoFlush=autoFlush;
            this->trouble=false;
            this->closing=false;
            this->charOut=new JOutputStreamWriter(this, encoding);
            this->textOut=new JBufferedWriter(charOut);
        }


        JPrintStream::JPrintStream(JFile* file, jbool autoFlush, JString* encoding):JFilterOutputStream(null,getClazz()) {
        	this->out=new JFileOutputStream(file);
			this->autoFlush=autoFlush;
			this->trouble=false;
			this->closing=false;
			this->charOut=new JOutputStreamWriter(this, encoding);
			this->textOut=new JBufferedWriter(charOut);
        }

        void JPrintStream::ensureOpen(){
            if (out == null){
                throw new JIOException(new JString("Stream closed"));
            }
        }

        void JPrintStream::flush() {
            synchronized (this,{
                try {
                    ensureOpen();
                    out->flush();
                }catch (JIOException* x) {
                    trouble = true;
                }
            })
        }

        void JPrintStream::close() {
            synchronized (this, {
                if (! closing) {
                    closing = true;
                    try {
                        textOut->close();
                        out->close();
                    }catch (JIOException* x) {
                        trouble = true;
                    }
                    textOut = null;
                    charOut = null;
                    out = null;
                }
            })
        }

        jbool JPrintStream::checkError() {
            if (out != null){
                flush();
            }
            if (out->isInstanceOf(JPrintStream::getClazz())) {
                JPrintStream* ps = dynamic_cast<JPrintStream*>(out);
                return ps->checkError();
            }
            return trouble;
        }

        void JPrintStream::setError() {
            trouble = true;
        }

        void JPrintStream::clearError() {
            trouble = false;
        }

        void JPrintStream::write(jint b) {
            try {
                synchronized (this, {
                    ensureOpen();
                    out->write(b);
                    if ((b == '\n') && autoFlush){
                        out->flush();
                    }
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintStream::write(JPrimitiveByteArray* buf, jint off, jint len) {
            try {
                synchronized (this,{
                    ensureOpen();
                    out->write(buf, off, len);
                    if (autoFlush){
                        out->flush();
                    }
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintStream::write(JPrimitiveCharArray* buf) {
            try {
                synchronized (this, {
                    ensureOpen();
                    textOut->write(buf);
                    textOut->flushBuffer();
                    charOut->flush();
                    if (autoFlush) {
                        for (jint i = 0; i < buf->size(); i++){
                            if (buf->getChar(i) == '\n'){
                                out->flush();
                            }
                        }
                    }
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintStream::write(JString* s) {
            try {
                synchronized (this, {
                    ensureOpen();
                    textOut->write(s);
                    textOut->flushBuffer();
                    charOut->flush();
                    if (autoFlush && (s->indexOf('\n') >= 0)){
                        out->flush();
                    }
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintStream::newLine() {
            try {
                synchronized (this,{
                    ensureOpen();
                    textOut->newLine();
                    textOut->flushBuffer();
                    charOut->flush();
                    if (autoFlush){
                        out->flush();
                    }
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintStream::print(jbool b) {
            write(b ? JBoolean::TRUE_STRING : JBoolean::FALSE_STRING);
        }

        void JPrintStream::print(jchar c) {
            write(JString::valueOf(c));
        }

        void JPrintStream::print(jint i) {
            write(JString::valueOf(i));
        }

        void JPrintStream::print(jlong l) {
            write(JString::valueOf(l));
        }

        void JPrintStream::print(jfloat f) {
            write(JString::valueOf(f));
        }

        void JPrintStream::print(jdouble d) {
            write(JString::valueOf(d));
        }

        void JPrintStream::print(JPrimitiveCharArray* s) {
            write(s);
        }

        void JPrintStream::print(JString* s) {
            if (s == null) {
                s = JString::NULL_STRING;
            }
            write(s);
        }

        void JPrintStream::print(JObject* obj) {
            write(JString::valueOf(obj));
        }

        void JPrintStream::println() {
            newLine();
        }

        void JPrintStream::println(jbool x) {
            synchronized (this,{
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(jchar x) {
            synchronized (this,{
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(jint x) {
            synchronized (this, {
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(jlong x) {
            synchronized (this, {
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(jfloat x) {
            synchronized (this, {
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(jdouble x) {
            synchronized (this, {
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(JPrimitiveCharArray* x) {
            synchronized (this, {
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(JString* x) {
            synchronized (this, {
                print(x);
                newLine();
            })
        }

        void JPrintStream::println(JObject* x) {
            JString* s = JString::valueOf(x);
            synchronized (this, {
                print(s);
                newLine();
            })
        }

        JPrintStream* JPrintStream::append(JCharSequence* csq) {
            if (csq == null){
                print(JString::NULL_STRING);
            }else{
                print(csq->toString());
            }
            return this;
        }

        JPrintStream* JPrintStream::append(JCharSequence* csq, jint start, jint end) {
            JCharSequence* cs = (csq == null ? JString::NULL_STRING : csq);
            write(cs->subSequence(start, end)->toString());
            return this;
        }

        JPrintStream* JPrintStream::append(jchar c) {
            print(c);
            return this;
        }

        JPrintStream::~JPrintStream(){
        }
    }
}

