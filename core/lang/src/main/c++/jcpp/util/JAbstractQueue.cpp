#include "jcpp/util/JAbstractQueue.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace util{
        class JAbstractQueueClass : public JClass{
        public:
            JAbstractQueueClass():JClass(){
                this->canonicalName=new JString("java.util.AbstractQueue");
                this->name=new JString("java.util.AbstractQueue");
                this->simpleName=new JString("AbstractQueue");
            }

            virtual void initialize(){
                addInterface(JQueue::getClazz());
            }

            JClass* getSuperclass(){
                return JAbstractCollection::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JAbstractQueue::getClazz(){
            if (clazz==null){
                clazz=new JAbstractQueueClass();
            }
            return clazz;
        }

        JAbstractQueue::JAbstractQueue(jcpp::lang::JClass* _class):JAbstractCollection(_class){
        }

        jbool JAbstractQueue::add(JObject* e){
            if (offer(e)){
                return true;
            }else{
                throw new JIllegalStateException(new JString("Queue full"));
            }
        }

        JObject* JAbstractQueue::remove(){
            JObject* x=poll();
            if (x!=null){
                return x;
            }else{
                throw new JNoSuchElementException();
            }

        }

        JObject* JAbstractQueue::element(){
            JObject* x=peek();
            if (x!=null){
                return x;
            }else{
                throw new JNoSuchElementException();
            }
        }

        void JAbstractQueue::clear(){
            while (poll()!=null){
                ;
            }
        }

        jbool JAbstractQueue::addAll(JCollection* c){
            if (c == null){
                throw new JNullPointerException();
            }
            if (c == (JAbstractCollection*)this){
                throw new JIllegalArgumentException();
            }
            jbool modified = false;
            JIterator* i=c->iterator();
            while (i->hasNext()){
                JObject* e=i->next();
                if (add(e)){
                    modified = true;
                }
            }
            return modified;
        }

        JAbstractQueue::~JAbstractQueue(){
        }
    }
}
