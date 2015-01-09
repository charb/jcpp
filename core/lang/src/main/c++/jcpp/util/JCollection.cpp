#include "jcpp/util/JCollection.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        class JCollectionClass : public jcpp::lang::JClass{

        public:
            JCollectionClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.Collection");
                this->name=new JString("java.util.Collection");
                this->simpleName=new JString("Collection");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JCollection::getClazz(){
            if (clazz==null){
                clazz=new JCollectionClass();
            }
            return clazz;
        }

        JCollection::~JCollection(){
        }
    }
}
