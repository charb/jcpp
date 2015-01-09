#include "jcpp/util/concurrent/JSynchronousQueue.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JSynchronousQueue::JSynchronousQueue():JAbstractQueue(getClazz()){
                elements=new JArrayList();
                waitingToTake=0;
            }

            jbool JSynchronousQueue::add(JObject* e){
                return JAbstractQueue::add(e);
            }

            JObject* JSynchronousQueue::remove(){
                return JAbstractQueue::remove();
            }

            JObject* JSynchronousQueue::element(){
                return JAbstractQueue::element();
            }

            void JSynchronousQueue::put(JObject* e){
                synchronized(elements,{
                    elements->add(e);
                    elements->notifyAll();
                    while (elements->size()>0){
                        elements->wait();
                    }
                })
            }

            jbool JSynchronousQueue::offer(JObject* e,jlong l){
                synchronized(elements,{
                    elements->add(e);
                    elements->notifyAll();
                    while (l>0 && elements->size()>0){
                        jlong l1=JSystem::currentTimeMillis();
                        elements->wait(l);
                        l1=JSystem::currentTimeMillis()-l1;
                        l-=l1;
                    }
                    if (elements->size()>0){
                        return false;
                    }
                    return true;
                })
            }

            jbool JSynchronousQueue::offer(JObject* e){
                synchronized(elements,{
                    if (waitingToTake>0){
                        elements->add(e);
                        elements->notifyAll();
                        return true;
                    }
                    return false;
                })
            }

            JObject* JSynchronousQueue::take(){
                synchronized(elements,{
                    waitingToTake++;
                    while (elements->size()==0){
                        elements->wait();
                    }
                    waitingToTake--;
                    return elements->remove(0);
                })
            }

            JObject* JSynchronousQueue::poll(jlong l){
                synchronized(elements,{
                    waitingToTake++;
                    while (l>0 && elements->size()==0){
                        jlong l1=JSystem::currentTimeMillis();
                        elements->wait(l);
                        l1=JSystem::currentTimeMillis()-l1;
                        l-=l1;
                    }
                    waitingToTake--;
                    if (elements->size()>0){
                        return elements->remove(0);
                    }
                    return null;
                })
            }

            JObject* JSynchronousQueue::poll(){
                synchronized(elements,{
                    if (elements->size()>0){
                        return elements->remove(0);
                    }
                    return null;
                })
            }

            jbool JSynchronousQueue::isEmpty(){
                return true;
            }

            jint JSynchronousQueue::size(){
                return 0;
            }

            jint JSynchronousQueue::remainingCapacity(){
                return 0;
            }

            void JSynchronousQueue::clear(){
            }

            jbool JSynchronousQueue::contains(JObject* o){
                return false;
            }

            jbool JSynchronousQueue::remove(JObject* o){
                return false;
            }

            jbool JSynchronousQueue::containsAll(JCollection* c){
                return c->isEmpty();
            }

            jbool JSynchronousQueue::removeAll(JCollection* c){
                return false;
            }

            jbool JSynchronousQueue::retainAll(JCollection* c){
                return false;
            }

            JObject* JSynchronousQueue::peek(){
                return null;
            }

            JIterator* JSynchronousQueue::iterator(){
                return JCollections::emptyIterator();
            }

            JPrimitiveObjectArray* JSynchronousQueue::toArray(){
                return new JPrimitiveObjectArray(JObject::getClazz(),0);
            }

            JPrimitiveObjectArray* JSynchronousQueue::toArray(JPrimitiveObjectArray* a){
                if (a->size() > 0){
                    a->set(0, null);
                }
                return a;
            }

            jint JSynchronousQueue::drainTo(JCollection* c){
                if (c == null){
                    throw new JNullPointerException();
                }
                if (c == this){
                    throw new JIllegalArgumentException();
                }
                jint n = 0;
                for (JObject* e=null; (e = poll()) != null;) {
                    c->add(e);
                    ++n;
                }
                return n;
            }
            
            jint JSynchronousQueue::drainTo(JCollection* c,jint max){
                if (c == null){
                    throw new JNullPointerException();
                }
                if (c == this){
                    throw new JIllegalArgumentException();
                }
                jint n = 0;
                for (JObject* e=null; n < max && (e = poll()) != null;) {
                    c->add(e);
                    ++n;
                }
                return n;
            }

            JSynchronousQueue::~JSynchronousQueue(){
            }
        }
    }
}
