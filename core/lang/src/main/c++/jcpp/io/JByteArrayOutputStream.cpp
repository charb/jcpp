#include "jcpp/io/JByteArrayOutputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::util;

namespace jcpp{
    namespace io{

        JByteArrayOutputStream::JByteArrayOutputStream(jint size):JOutputStream(getClazz()){
            buf=new JPrimitiveByteArray(size);
            count=0;
        }

        void JByteArrayOutputStream::ensureCapacity(jint minCapacity) {
            if (minCapacity - buf->size() > 0){
                grow(minCapacity);
            }
        }

        void JByteArrayOutputStream::grow(jint minCapacity) {
            jint oldCapacity = buf->size();
            jint newCapacity = oldCapacity << 1;
            if (newCapacity - minCapacity < 0){
                newCapacity = minCapacity;
            }
            if (newCapacity < 0) {
                if (minCapacity < 0){
                    throw new JOutOfMemoryError();
                }
                newCapacity = JInteger::MAX_VALUE;
            }
            buf = JArrays::copyOf(buf, newCapacity);
        }

        void JByteArrayOutputStream::write(jint b){
            synchronized(this,{
                ensureCapacity(count + 1);
                buf->setByte(count,(jbyte) b);
                count += 1;
            })
        }

        void JByteArrayOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            synchronized(this,{
                if ((off < 0) || (off > b->size()) || (len < 0) || ((off + len) - b->size() > 0)) {
                    throw new JIndexOutOfBoundsException();
                }
                ensureCapacity(count + len);
                JSystem::arraycopy(b, off, buf, count, len);
            })
        }

        void  JByteArrayOutputStream::writeTo(JOutputStream* out){
            synchronized(this,{
                out->write(buf,0,buf->size());
            })
        }

        void  JByteArrayOutputStream::reset(){
            synchronized(this,{
                count=0;
            })
        }

        JPrimitiveByteArray* JByteArrayOutputStream::toByteArray(){
            synchronized(this,{
                return JArrays::copyOf(buf, count);
            })
        }

        jint JByteArrayOutputStream::size(){
            synchronized(this,{
                return count;
            })
        }

        JString* JByteArrayOutputStream::toString(){
            synchronized(this,{
                return new JString(buf,0,count);
            })
        }

        void JByteArrayOutputStream::close(){
        }

        JByteArrayOutputStream::~JByteArrayOutputStream(){
        }
    }
}
