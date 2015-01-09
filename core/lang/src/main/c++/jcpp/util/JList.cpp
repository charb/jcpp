#include "jcpp/util/JList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JCollection.h"

namespace jcpp{
    namespace util{
        class JListClass : public jcpp::lang::JClass{

        public:
            JListClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.List");
                this->name=new JString("java.util.List");
                this->simpleName=new JString("List");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JCollection::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JList::getClazz(){
            if (clazz==null){
                clazz=new JListClass();
            }
            return clazz;
        }

        JList::~JList(){
        }
    }
}
