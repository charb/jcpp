#include "jcpp/util/concurrent/atomic/JAtomicLongArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JLong.h"
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

                JAtomicLongArray::JAtomicLongArray(jint l):JObject(getClazz()){
                    this->array=new JPrimitiveLongArray(l);
                }

                JAtomicLongArray::JAtomicLongArray():JObject(getClazz()){
                    this->array=new JPrimitiveLongArray(0);
                }

                jint JAtomicLongArray::length(){
                    synchronized(this,{
                        return array->size();
                    })
                }

                jlong JAtomicLongArray::get(jint index){
                    synchronized(this,{
                        return array->getLong(index);
                    })
                }

                void JAtomicLongArray::set(jint index,jlong value){
                    synchronized(this,{
                        this->array->setLong(index,value);
                    })
                }

                void JAtomicLongArray::lazySet(jint index,jlong value){
                    set(index,value);
                }

                jlong JAtomicLongArray::getAndSet(jint index,jlong value){
                    synchronized(this,{
                        jlong prev=this->array->getLong(index);
                        this->array->setLong(index,value);
                        return prev;
                    })
                }

                jbool JAtomicLongArray::compareAndSet(jint index,jlong expect,jlong update){
                    synchronized(this,{
                        if (expect==array->getLong(index)){
                            array->setLong(index,update);
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicLongArray::weakCompareAndSet(jint index,jlong expect, jlong update){
                    return compareAndSet(index,expect,update);
                }

                jlong JAtomicLongArray::getAndIncrement(jint index){
                    synchronized(this,{
                        jlong v=array->getLong(index);
                        array->setLong(index,array->getLong(index)+1);
                        return v;
                    })
                }

                jlong JAtomicLongArray::getAndDecrement(jint index){
                    synchronized(this,{
                        jlong v=array->getLong(index);
                        array->setLong(index,array->getLong(index)-1);
                        return v;
                    })
                }

                jlong JAtomicLongArray::getAndAdd(jint index,jlong delta){
                    synchronized(this,{
                        jlong v=array->getLong(index);
                        array->setLong(index,array->getLong(index)+delta);
                        return v;
                    })
                }

                jlong JAtomicLongArray::incrementAndGet(jint index){
                    synchronized(this,{
                        array->setLong(index,array->getLong(index)+1);
                        return array->getLong(index);
                    })
                }

                jlong JAtomicLongArray::decrementAndGet(jint index){
                    synchronized(this,{
                        array->setLong(index,array->getLong(index)-1);
                        return array->getLong(index);
                    })
                }

                jlong JAtomicLongArray::addAndGet(jint index,jlong delta){
                    synchronized(this,{
                        array->setLong(index,array->getLong(index)+delta);
                        return array->getLong(index);
                    })
                }

                JString* JAtomicLongArray::toString(){
                    synchronized(this,{
                        jint iMax = array->size() - 1;
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

                JAtomicLongArray::~JAtomicLongArray(){
                }
            }
        }
    }
}
