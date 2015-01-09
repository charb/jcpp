#include "jcpp/lang/JReadable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JReadableClass : public jcpp::lang::JClass{
            public:
                JReadableClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.lang.Readable");
                    this->name=new JString("java.lang.Readable");
                    this->simpleName=new JString("Readable");
                    this->bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JReadable::getClazz(){
            if (clazz==null){
                clazz=new JReadableClass();
            }
            return clazz;
        }

        JReadable::~JReadable(){
        }
    }
}
