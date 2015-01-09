#include "jcpp/io/JPrintWriter.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/io/JBufferedWriter.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JPrintWriter::JPrintWriter(JWriter* out,jbool autoFlush):JWriter(getClazz(),out){
            this->out=out;
            this->autoFlush=autoFlush;
            this->trouble=false;
            if (out->isInstanceOf(JPrintStream::getClazz())){
                psOut=dynamic_cast<JPrintStream*>(out);
            }
        }

        JPrintWriter::JPrintWriter(JOutputStream* out,jbool autoFlush):JWriter(getClazz()){
            this->out=new JBufferedWriter(new JOutputStreamWriter(out));
            this->lock=out;
            this->autoFlush=autoFlush;
            this->trouble=false;
            if (out->isInstanceOf(JPrintStream::getClazz())){
                psOut=dynamic_cast<JPrintStream*>(out);
            }
        }

        JPrintWriter::JPrintWriter(JString* fileName,jbool autoFlush):JWriter(getClazz()){
            this->out=new JBufferedWriter(new JOutputStreamWriter(new JFileOutputStream(fileName)));
            this->lock=out;
            this->autoFlush=autoFlush;
            this->trouble=false;
            if (out->isInstanceOf(JPrintStream::getClazz())){
                psOut=dynamic_cast<JPrintStream*>(out);
            }
        }

        JPrintWriter::JPrintWriter(JFile* file,jbool autoFlush):JWriter(getClazz()){
            this->out=new JBufferedWriter(new JOutputStreamWriter(new JFileOutputStream(file)));
            this->lock=out;
            this->autoFlush=autoFlush;
            this->trouble=false;
            if (out->isInstanceOf(JPrintStream::getClazz())){
                psOut=dynamic_cast<JPrintStream*>(out);
            }
        }

        void JPrintWriter::ensureOpen(){
            if (out == null){
                throw new JIOException(new JString("Stream closed"));
            }
        }

        void JPrintWriter::flush() {
            synchronized (lock,{
                try {
                    ensureOpen();
                    out->flush();
                }catch (JIOException* x) {
                    trouble = true;
                }
            })
        }

        void JPrintWriter::close() {
            try {
                synchronized (lock,{
                    if (out == null){
                        return;
                    }
                    out->close();
                    out = null;
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        jbool JPrintWriter::checkError() {
            if (out != null){
                flush();
            }
            if (out->isInstanceOf(JPrintWriter::getClazz())) {
                JPrintWriter* ps = dynamic_cast<JPrintWriter*>(out);
                return ps->checkError();

            }else if (psOut != null) {
                return psOut->checkError();
            }
            return trouble;
        }

        void JPrintWriter::setError() {
            trouble = true;
        }

        void JPrintWriter::clearError() {
            trouble = false;
        }

        void JPrintWriter::write(jint b) {
            try {
                synchronized (lock, {
                    ensureOpen();
                    out->write(b);
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintWriter::write(JPrimitiveCharArray* buf, jint off, jint len) {
            try {
                synchronized (lock,{
                    ensureOpen();
                    out->write(buf, off, len);
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintWriter::write(JPrimitiveCharArray* buf) {
            write(buf,0,buf->size());
        }

        void JPrintWriter::write(JString* s, jint off, jint len) {
            try {
                synchronized (lock, {
                    ensureOpen();
                    out->write(s, off, len);
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintWriter::write(JString* s) {
            write(s, 0, s->length());
        }

        void JPrintWriter::newLine() {
            try {
                synchronized (lock,{
                    ensureOpen();
                    out->write(JSystem::lineSeparator());
                    if (autoFlush){
                        out->flush();
                    }
                })
            }catch (JIOException* x) {
                trouble = true;
            }
        }

        void JPrintWriter::print(jbool b) {
            write(b ? JBoolean::TRUE_STRING : JBoolean::FALSE_STRING);
        }

        void JPrintWriter::print(jchar c) {
            write(JString::valueOf(c));
        }

        void JPrintWriter::print(jint i) {
            write(JString::valueOf(i));
        }

        void JPrintWriter::print(jlong l) {
            write(JString::valueOf(l));
        }

        void JPrintWriter::print(jfloat f) {
            write(JString::valueOf(f));
        }

        void JPrintWriter::print(jdouble d) {
            write(JString::valueOf(d));
        }

        void JPrintWriter::print(JPrimitiveCharArray* s) {
            write(s);
        }

        void JPrintWriter::print(JString* s) {
            if (s == null) {
                s = JString::NULL_STRING;
            }
            write(s);
        }

        void JPrintWriter::print(JObject* obj) {
            write(JString::valueOf(obj));
        }

        void JPrintWriter::println() {
            newLine();
        }

        void JPrintWriter::println(jbool x) {
            synchronized (lock,{
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(jchar x) {
            synchronized (lock,{
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(jint x) {
            synchronized (lock, {
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(jlong x) {
            synchronized (lock, {
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(jfloat x) {
            synchronized (lock, {
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(jdouble x) {
            synchronized (lock, {
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(JPrimitiveCharArray* x) {
            synchronized (lock, {
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(JString* x) {
            synchronized (lock, {
                print(x);
                newLine();
            })
        }

        void JPrintWriter::println(JObject* x) {
            JString* s = JString::valueOf(x);
            synchronized (lock, {
                print(s);
                newLine();
            })
        }

        JPrintWriter* JPrintWriter::append(JCharSequence* csq) {
            if (csq == null){
                write(JString::NULL_STRING);
            }else{
                write(csq->toString());
            }
            return this;
        }

        JPrintWriter* JPrintWriter::append(JCharSequence* csq, jint start, jint end) {
            JCharSequence* cs = (csq == null ? JString::NULL_STRING : csq);
            write(cs->subSequence(start, end)->toString());
            return this;
        }

        JPrintWriter* JPrintWriter::append(jchar c) {
            write(c);
            return this;
        }

        JPrintWriter::~JPrintWriter(){
        }
    }
}

