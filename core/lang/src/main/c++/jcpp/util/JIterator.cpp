#include "jcpp/util/JIterator.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        class JIteratorClass : public jcpp::lang::JClass{

        public:
          JIteratorClass():jcpp::lang::JClass(){
              this->canonicalName=new JString("java.util.Iterator");
              this->name=new JString("java.util.Iterator");
              this->simpleName=new JString("Iterator");
              this->bIsInterface=true;
          }

          virtual jcpp::lang::JClass* getSuperclass(){
              return JInterface::getClazz();
          }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JIterator::getClazz(){
            if (clazz==null){
                clazz=new JIteratorClass();
            }
            return clazz;
        }

        JIterator::~JIterator(){
        }
    }
}

