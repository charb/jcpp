#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInteger.h"
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

                JAtomicInteger::JAtomicInteger():JNumber(getClazz()){
                    value=new JPrimitiveInt(0);
                }

                JAtomicInteger::JAtomicInteger(jint value):JNumber(getClazz()){
                    this->value=new JPrimitiveInt(value);
                }

                jint JAtomicInteger::get(){
                    synchronized(this,{
                        return value->get();
                    })
                }

                void JAtomicInteger::set(jint value){
                    synchronized(this,{
                        this->value->set(value);
                    })
                }

                void JAtomicInteger::lazySet(jint value){
                    set(value);
                }

                jint JAtomicInteger::getAndSet(jint value){
                    synchronized(this,{
                        jint prev=this->value->get();
                        this->value->set(value);
                        return prev;
                    })
                }

                jbool JAtomicInteger::compareAndSet(jint expect,jint update){
                    synchronized(this,{
                        if (expect==value->get()){
                            value->set(update);
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicInteger::weakCompareAndSet(jint expect, jint update){
                    return compareAndSet(expect,update);
                }

                jint JAtomicInteger::getAndIncrement(){
                    synchronized(this,{
                        jint v=value->get();
                        value->set(value->get()+1);
                        return v;
                    })
                }

                jint JAtomicInteger::getAndDecrement(){
                    synchronized(this,{
                        jint v=value->get();
                        value->set(value->get()-1);
                        return v;
                    })
                }

                jint JAtomicInteger::getAndAdd(jint delta){
                    synchronized(this,{
                        jint v=value->get();
                        value->set(value->get()+delta);
                        return v;
                    })
                }

                jint JAtomicInteger::incrementAndGet(){
                    synchronized(this,{
                        value->set(value->get()+1);
                        return value->get();
                    })
                }

                jint JAtomicInteger::decrementAndGet(){
                    synchronized(this,{
                        value->set(value->get()-1);
                        return value->get();
                    })
                }

                jint JAtomicInteger::addAndGet(jint delta){
                    synchronized(this,{
                        value->set(value->get()+delta);
                        return value->get();
                    })
                }

                JString* JAtomicInteger::toString(){
                    return JInteger::toString(get());
                }

                jint JAtomicInteger::intValue(){
                    return get();
                }

                jlong JAtomicInteger::longValue(){
                    return (jlong)get();
                }

                jfloat JAtomicInteger::floatValue(){
                    return (jfloat)get();
                }

                jdouble JAtomicInteger::doubleValue(){
                    return (jdouble)get();
                }

                JAtomicInteger::~JAtomicInteger(){
                }
            }
        }
    }
}
