#include "jcpp/util/concurrent/atomic/JAtomicBoolean.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JBoolean.h"
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

                JAtomicBoolean::JAtomicBoolean():JObject(getClazz()){
                    value=new JPrimitiveInt(0);
                }

                JAtomicBoolean::JAtomicBoolean(jbool value):JObject(getClazz()){
                    this->value=new JPrimitiveInt(value?1:0);
                }

                jbool JAtomicBoolean::get(){
                    synchronized(this,{
                        return value->get()==1;
                    })
                }

                jbool JAtomicBoolean::compareAndSet(jbool expect,jbool update){
                    synchronized(this,{
                        jint iexpect=(expect?1:0);
                        if (iexpect==value->get()){
                            value->set(update?1:0);
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicBoolean::weakCompareAndSet(jbool expect, jbool update){
                    return compareAndSet(expect,update);
                }

                void JAtomicBoolean::set(jbool value){
                    synchronized(this,{
                        this->value->set(value?1:0);
                    })
                }

                void JAtomicBoolean::lazySet(jbool value){
                    set(value);
                }

                jbool JAtomicBoolean::getAndSet(jbool value){
                    synchronized(this,{
                        jbool prev=false;
                        do {
                            prev = get();
                        } while (!compareAndSet(prev, value));
                        return prev;
                    })
                }

                JString* JAtomicBoolean::toString(){
                    return JBoolean::toString(get());
                }

                JAtomicBoolean::~JAtomicBoolean(){
                }
            }
        }
    }
}
