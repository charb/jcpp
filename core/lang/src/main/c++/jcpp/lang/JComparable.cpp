#include "jcpp/lang/JComparable.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

        class JComparableClass : public jcpp::lang::JClass{
          public:
            JComparableClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Comparable");
                this->name=new JString("java.lang.Comparable");
                this->simpleName=new JString("Comparable");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JComparable::getClazz(){
            if (clazz==null){
                clazz=new JComparableClass();
            }
            return clazz;
        }

        JComparable::~JComparable(){
        }
    }
}

