#include "jcpp/util/JQueue.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/util/JCollection.h"

namespace jcpp{
    namespace util{
        class JQueueClass : public JClass{
        public:
            JQueueClass():JClass(){
                this->canonicalName=new JString("java.util.Queue");
                this->name=new JString("java.util.Queue");
                this->simpleName=new JString("Queue");
                this->bIsInterface=true;
            }

            JClass* getSuperclass(){
                return JCollection::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JQueue::getClazz(){
            if (clazz==null){
                clazz=new JQueueClass();
            }
            return clazz;
        }

        JQueue::~JQueue(){
        }
    }
}
