#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JNumberClass : public jcpp::lang::JClass{
          public:
            JNumberClass(){
                this->canonicalName=new JString("java.lang.Number");
                this->name=new JString("java.lang.Number");
                this->simpleName=new JString("Number");
                this->serialVersionUID=-8742448824652078965ULL;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        JNumber::JNumber(jcpp::lang::JClass* _class):JObject(_class){
        }

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNumber::getClazz(){
            if (clazz==null){
                clazz=new JNumberClass();
            }
            return clazz;
        }

        JNumber::~JNumber(){
        }
    }
}
