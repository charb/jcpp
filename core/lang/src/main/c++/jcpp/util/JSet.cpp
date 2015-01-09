#include "jcpp/util/JSet.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JCollection.h"

namespace jcpp{
    namespace util{
        class JSetClass : public jcpp::lang::JClass{
        public:
            JSetClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.Set");
                this->name=new JString("java.util.Set");
                this->simpleName=new JString("Set");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JCollection::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JSet::getClazz(){
            if (clazz==null){
                clazz=new JSetClass();
            }
            return clazz;
        }

        JSet::~JSet(){
        }
    }
}
