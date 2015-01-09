#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCloneableClass : public jcpp::lang::JClass{
          public:
            JCloneableClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Cloneable");
                this->name=new JString("java.lang.Cloneable");
                this->simpleName=new JString("Cloneable");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JCloneable::getClazz(){
            if (clazz==null){
                clazz=new JCloneableClass();
            }
            return clazz;
        }

        JCloneable::~JCloneable(){
        }
    }
}
