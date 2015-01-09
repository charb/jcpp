#include "jcpp/util/JListIterator.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        class JListIteratorClass : public jcpp::lang::JClass{
        public:
            JListIteratorClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.ListIterator");
                this->name=new JString("java.util.ListIterator");
                this->simpleName=new JString("ListIterator");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JIterator::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JListIterator::getClazz(){
            if (clazz==null){
                clazz=new JListIteratorClass();
            }
            return clazz;
        }

        JListIterator::~JListIterator(){
        }
    }
}


