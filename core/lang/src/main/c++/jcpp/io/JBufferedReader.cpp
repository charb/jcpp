#include "jcpp/io/JBufferedReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JStringBuffer.h"

namespace jcpp{
    namespace io{

        static jint INVALIDATED = -2;
        static jint UNMARKED = -1;

        JBufferedReader::JBufferedReader(jcpp::lang::JClass* _class,JReader* in,jint sz):JReader(_class,in){
            this->in=in;
            cb = new JPrimitiveCharArray(sz);
            nextChar = 0;
            nChars = 0;
            markedChar = UNMARKED;
            readAheadLimit=0;
            skipLF=false;
            markedSkipLF=false;
        }

        JBufferedReader::JBufferedReader(JReader* in,jint sz):JReader(getClazz(),in){
            this->in=in;
            cb = new JPrimitiveCharArray(sz);
            nextChar = 0;
            nChars = 0;
            markedChar = UNMARKED;
            readAheadLimit=0;
            skipLF=false;
            markedSkipLF=false;
        }

        void JBufferedReader::ensureOpen(){
            synchronized(lock,{
                if (in == null){
                    throw new JIOException(new JString("Stream closed"));
                }
            })
        }

        void JBufferedReader::fill(){
            jint dst=0;
            if (markedChar <= UNMARKED) {
                dst = 0;
            } else {
                jint delta = nextChar - markedChar;
                if (delta >= readAheadLimit) {
                    markedChar = INVALIDATED;
                    readAheadLimit = 0;
                    dst = 0;
                } else {
                    if (readAheadLimit <= length) {
                        JSystem::arraycopy(cb, markedChar, cb, 0, delta);
                        markedChar = 0;
                        dst = delta;
                    } else {
                        JPrimitiveCharArray* ncb = new JPrimitiveCharArray(readAheadLimit);
                        JSystem::arraycopy(cb, markedChar, ncb, 0, delta);
                        cb = ncb;
                        markedChar = 0;
                        dst = delta;
                    }
                    nextChar = nChars = delta;
                }
            }
            jint n;
            do {
                n = in->read(cb, dst, cb->size() - dst);
            } while (n == 0);
            if (n > 0) {
                nChars = dst + n;
                nextChar = dst;
            }
        }

        jint JBufferedReader::read(){
            synchronized(lock,{
                ensureOpen();
                for (;;) {
                    if (nextChar >= nChars) {
                        fill();
                        if (nextChar >= nChars){
                            return -1;
                        }
                    }
                    if (skipLF) {
                        skipLF = false;
                        if (cb->getChar(nextChar) == '\n') {
                            nextChar++;
                            continue;
                        }
                    }
                    return cb->getChar(nextChar++);
                }
            })
        }

        jint JBufferedReader::read1(JPrimitiveCharArray* cbuf, jint off,jint len){
            if (nextChar >= nChars) {
                if (len >= length && markedChar <= UNMARKED && !skipLF) {
                    return in->read(cbuf, off, len);
                }
                fill();
            }
            if (nextChar >= nChars){
                return -1;
            }
            if (skipLF) {
                skipLF = false;
                if (cb->getChar(nextChar) == '\n') {
                    nextChar++;
                    if (nextChar >= nChars){
                        fill();
                    }
                    if (nextChar >= nChars){
                        return -1;
                    }
                }
            }
            jint n = (len < nChars - nextChar ? len : nChars - nextChar);
            JSystem::arraycopy(cb, nextChar, cbuf, off, n);
            nextChar += n;
            return n;
        }

        jint JBufferedReader::read(JPrimitiveCharArray* cbuf, jint off,jint len){
            synchronized(lock,{
                ensureOpen();
                if ((off < 0) || (len < 0) || ((off + len) < 0)) {
                    throw new JIndexOutOfBoundsException();
                } else if (len == 0) {
                    return 0;
                }

                jint n = read1(cbuf, off, len);
                if (n <= 0){
                    return n;
                }
                while ((n < len) && in->ready()) {
                    jint n1 = read1(cbuf, off + n, len - n);
                    if (n1 <= 0){
                        break;
                    }
                    n += n1;
                }
                return n;
            })
        }

        JString* JBufferedReader::readLine(jbool ignoreLF){
            synchronized(lock,{
                JStringBuffer* s = 0;
                jint startChar=0;
                ensureOpen();

                jbool omitLF = ignoreLF || skipLF;

                for (;;) {
                    if (nextChar >= nChars){
                        fill();
                    }
                    if (nextChar >= nChars) {
                        if (s != null && s->length() > 0){
                            return s->toString();
                        }else{
                            return null;
                        }
                    }
                    jbool eol = false;
                    jchar c = 0;
                    jint i=0;

                    if (omitLF && (cb->getChar(nextChar) == '\n')){
                        nextChar++;
                    }
                    skipLF = false;
                    omitLF = false;

                    for (i = nextChar; i < nChars; i++) {
                        c = cb->getChar(i);
                        if ((c == '\n') || (c == '\r')) {
                            eol = true;
                            break;
                        }
                    }

                    startChar = nextChar;
                    nextChar = i;

                    if (eol) {
                        JString* str=0;
                        if (s == null) {
                            str=new JString(cb,startChar,i-startChar);
                        } else {
                            s->append(cb, startChar, i - startChar);
                            str = s->toString();
                        }
                        nextChar++;
                        if (c == '\r') {
                            skipLF = true;
                        }
                        return str;
                    }

                    if (s == null){
                         s = new JStringBuffer();
                    }
                    s->append(cb, startChar, i - startChar);
                 }
             })
        }

        JString* JBufferedReader::readLine(){
            return readLine(false);
        }

        jlong JBufferedReader::skip(jlong n){
            synchronized(lock,{
                ensureOpen();
                jlong r = n;
                while (r > 0) {
                    if (nextChar >= nChars){
                        fill();
                    }
                    if (nextChar >= nChars){
                        break;
                    }
                    if (skipLF) {
                        skipLF = false;
                        if (cb->getChar(nextChar) == '\n') {
                            nextChar++;
                        }
                    }
                    jlong d = nChars - nextChar;
                    if (r <= d) {
                        nextChar += r;
                        r = 0;
                        break;
                    }else {
                        r -= d;
                        nextChar = nChars;
                    }
                }
                return n - r;
            })
        }

        jbool JBufferedReader::ready(){
            synchronized(lock,{
                ensureOpen();
                if (skipLF) {
                    if (nextChar >= nChars && in->ready()) {
                        fill();
                    }
                    if (nextChar < nChars) {
                        if (cb->getChar(nextChar) == '\n'){
                            nextChar++;
                        }
                        skipLF = false;
                    }
                }
                jbool b=(nextChar < nChars) || in->ready();
                return b;
            })
        }

        jbool JBufferedReader::markSupported(){
            return true;
        }

        void JBufferedReader::mark(jint m){
            synchronized(lock,{
                ensureOpen();
                this->readAheadLimit = m;
                markedChar = nextChar;
                markedSkipLF = skipLF;
            })
        }

        void JBufferedReader::reset(){
            synchronized(lock,{
                ensureOpen();
                if (markedChar < 0){
                    JString* m=new JString((markedChar == INVALIDATED) ? "Mark invalid" : "Stream not marked");
                    throw new JIOException(m);
                }
                nextChar = markedChar;
                skipLF = markedSkipLF;
            })
        }

        void JBufferedReader::close(){
            synchronized(lock,{
                if (in == null){
                    return;
                }
                in->close();
                in = null;
                cb = null;
            })
        }

        JBufferedReader::~JBufferedReader(){
        }
    }
}
