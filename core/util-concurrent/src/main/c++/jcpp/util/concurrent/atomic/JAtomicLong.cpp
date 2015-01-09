#include "jcpp/util/concurrent/atomic/JAtomicLong.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JLong.h"
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

                JAtomicLong::JAtomicLong():JNumber(getClazz()){
                    value=new JPrimitiveLong(0);
                }

                JAtomicLong::JAtomicLong(jlong value):JNumber(getClazz()){
                    this->value=new JPrimitiveLong(value);
                }

                jlong JAtomicLong::get(){
                    synchronized(this,{
                        return value->get();
                    })
                }

                void JAtomicLong::set(jlong value){
                    synchronized(this,{
                        this->value->set(value);
                    })
                }

                void JAtomicLong::lazySet(jlong value){
                    set(value);
                }

                jlong JAtomicLong::getAndSet(jlong value){
                    synchronized(this,{
                        jlong prev=this->value->get();
                        this->value->set(value);
                        return prev;
                    })
                }

                jbool JAtomicLong::compareAndSet(jlong expect,jlong update){
                    synchronized(this,{
                        if (expect==value->get()){
                            value->set(update);
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicLong::weakCompareAndSet(jlong expect, jlong update){
                    return compareAndSet(expect,update);
                }

                jlong JAtomicLong::getAndIncrement(){
                    synchronized(this,{
                        jlong v=value->get();
                        value->set(value->get()+1);
                        return v;
                    })
                }

                jlong JAtomicLong::getAndDecrement(){
                    synchronized(this,{
                        jlong v=value->get();
                        value->set(value->get()-1);
                        return v;
                    })
                }

                jlong JAtomicLong::getAndAdd(jlong delta){
                    synchronized(this,{
                        jlong v=value->get();
                        value->set(value->get()+delta);
                        return v;
                    })
                }

                jlong JAtomicLong::incrementAndGet(){
                    synchronized(this,{
                        value->set(value->get()+1);
                        return value->get();
                    })
                }

                jlong JAtomicLong::decrementAndGet(){
                    synchronized(this,{
                        value->set(value->get()-1);
                        return value->get();
                    })
                }

                jlong JAtomicLong::addAndGet(jlong delta){
                    synchronized(this,{
                        value->set(value->get()+delta);
                        return value->get();
                    })
                }

                JString* JAtomicLong::toString(){
                    return JLong::toString(get());
                }

                jint JAtomicLong::intValue(){
                    return (jint)get();
                }

                jlong JAtomicLong::longValue(){
                    return get();
                }

                jfloat JAtomicLong::floatValue(){
                    return (jfloat)get();
                }

                jdouble JAtomicLong::doubleValue(){
                    return (jdouble)get();
                }

                JAtomicLong::~JAtomicLong(){
                }
            }
        }
    }
}
