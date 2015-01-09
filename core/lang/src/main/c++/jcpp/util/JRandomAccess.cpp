#include "jcpp/util/JRandomAccess.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        class JRandomAccessClass : public jcpp::lang::JClass{
        public:
            JRandomAccessClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.RandomAccess");
                this->name=new JString("java.util.RandomAccess");
                this->simpleName=new JString("RandomAccess");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JRandomAccess::getClazz(){
            if (clazz==null){
                clazz=new JRandomAccessClass();
            }
            return clazz;
        }

        JRandomAccess::~JRandomAccess(){
        }
    }
}


