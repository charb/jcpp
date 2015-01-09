#include "jcpp/util/concurrent/atomic/JAtomicReference.h"
#include "jcpp/lang/JClass.h"
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

                JAtomicReference::JAtomicReference(JObject* value):JObject(getClazz()){
                    this->value=value;
                }

                JObject* JAtomicReference::get(){
                    synchronized(this,{
                        return value;
                    })
                }

                void JAtomicReference::set(JObject* value){
                    synchronized(this,{
                        this->value=value;
                    })
                }

                void JAtomicReference::lazySet(JObject* value){
                    set(value);
                }

                JObject* JAtomicReference::getAndSet(JObject* value){
                    synchronized(this,{
                        JObject* prev=this->value;
                        this->value=value;
                        return prev;
                    })
                }

                jbool JAtomicReference::compareAndSet(JObject* expect,JObject* update){
                    synchronized(this,{
                        if (expect==value){
                            value=update;
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicReference::weakCompareAndSet(JObject* expect, JObject* update){
                    return compareAndSet(expect,update);
                }

                JString* JAtomicReference::toString(){
                    return JString::valueOf(get());
                }

                JAtomicReference::~JAtomicReference(){
                }
            }
        }
    }
}
