#include "jcpp/util/concurrent/atomic/JAtomicReferenceArray.h"
#include "jcpp/lang/JClass.h"
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

                JAtomicReferenceArray::JAtomicReferenceArray(jint l):JObject(getClazz()){
                    this->value=new JPrimitiveObjectArray(JObject::getClazz(),l);
                }

                jint JAtomicReferenceArray::length(){
                    synchronized(this,{
                        return value->size();
                    })
                }

                JObject* JAtomicReferenceArray::get(jint index){
                    synchronized(this,{
                        return value->get(index);
                    })
                }

                void JAtomicReferenceArray::set(jint index,JObject* value){
                    synchronized(this,{
                        this->value->set(index,value);
                    })
                }

                void JAtomicReferenceArray::lazySet(jint index,JObject* value){
                    set(index,value);
                }

                JObject* JAtomicReferenceArray::getAndSet(jint index,JObject* value){
                    synchronized(this,{
                        JObject* prev=this->value->get(index);
                        this->value->set(index,value);
                        return prev;
                    })
                }

                jbool JAtomicReferenceArray::compareAndSet(jint index,JObject* expect,JObject* update){
                    synchronized(this,{
                        if (expect==value->get(index)){
                            value->set(index,update);
                            return true;
                        }
                        return false;
                    })
                }

                jbool JAtomicReferenceArray::weakCompareAndSet(jint index,JObject* expect, JObject* update){
                    return compareAndSet(index,expect,update);
                }

                JString* JAtomicReferenceArray::toString(){
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

                JAtomicReferenceArray::~JAtomicReferenceArray(){
                }
            }
        }
    }
}
