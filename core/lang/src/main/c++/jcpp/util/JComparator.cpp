#include "jcpp/util/JComparator.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        class JComparatorClass : public JClass{

        public:
          JComparatorClass():JClass(){
              this->canonicalName=new JString("java.util.Comparator");
              this->name=new JString("java.util.Comparator");
              this->simpleName=new JString("Comparator");
              this->bIsInterface=true;
          }

          virtual JClass* getSuperclass(){
              return JInterface::getClazz();
          }
        };

        static JClass* clazz;

        JClass* JComparator::getClazz(){
            if (clazz==null){
                clazz=new JComparatorClass();
            }
            return clazz;
        }

        JComparator::~JComparator(){
        }
    }
}

