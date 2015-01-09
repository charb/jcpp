#include "jcpp/util/concurrent/atomic/JAtomicIntegerArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

                JAtomicIntegerArray::JAtomicIntegerArray(jint l):JObject(getClazz()){
                    this->value=new JPrimitiveIntArray(l);
                }

                jint JAtomicIntegerArray::length(){
                    synchronized(this,{
                        return value->size();
                    })
                }

                jint JAtomicIntegerArray::get(jint index){
                    synchronized(this,{
                        return value->getInt(index);
                    })
                }

                void JAtomicIntegerArray::set(jint index,jint value){
                    synchronized(this,{
                        this->value->setInt(index,value);
                    })
                }

                void JAtomicIntegerArray::lazySet(jint index,jint value){
                    set(index,value);
                }

                jint JAtomicIntegerArray::getAndSet(jint index,jint value){
                    synchronized(this,{
                        jint prev=this->value->getInt(index);
                        this->value->setInt(index,value);
                        return prev;
                    })
                }

                jbool JAtomicIntegerArray::compareAndSet(jint index,jint expect,jint update){
                    synchronized(this,{
                        if (expect==value->getInt(index)){
                            value->setInt(index,update);
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicIntegerArray::weakCompareAndSet(jint index,jint expect, jint update){
                    return compareAndSet(index,expect,update);
                }

                jint JAtomicIntegerArray::getAndIncrement(jint index){
                    synchronized(this,{
                        jint v=value->getInt(index);
                        value->setInt(index,value->getInt(index)+1);
                        return v;
                    })
                }

                jint JAtomicIntegerArray::getAndDecrement(jint index){
                    synchronized(this,{
                        jint v=value->getInt(index);
                        value->setInt(index,value->getInt(index)-1);
                        return v;
                    })
                }

                jint JAtomicIntegerArray::getAndAdd(jint index,jint delta){
                    synchronized(this,{
                        jint v=value->getInt(index);
                        value->setInt(index,value->getInt(index)+delta);
                        return v;
                    })
                }

                jint JAtomicIntegerArray::incrementAndGet(jint index){
                    synchronized(this,{
                        value->setInt(index,value->getInt(index)+1);
                        return value->getInt(index);
                    })
                }

                jint JAtomicIntegerArray::decrementAndGet(jint index){
                    synchronized(this,{
                        value->setInt(index,value->getInt(index)-1);
                        return value->getInt(index);
                    })
                }

                jint JAtomicIntegerArray::addAndGet(jint index,jint delta){
                    synchronized(this,{
                        value->setInt(index,value->getInt(index)+delta);
                        return value->getInt(index);
                    })
                }

                JString* JAtomicIntegerArray::toString(){
                    synchronized(this,{
                        jint iMax = value->size() - 1;
                        if (iMax == -1){
                            return new JString("[]");
                        }

                        JStringBuilder* b = new JStringBuilder();
                        b->append('[');
                        for (jint i = 0; ; i++) {
                            b->append(get(i));
                            if (i == iMax){
                                return b->append(']')->toString();
                            }
                            b->append(',')->append(' ');
                        }
                    })
                }

                JAtomicIntegerArray::~JAtomicIntegerArray(){
                }
            }
        }
    }
}
