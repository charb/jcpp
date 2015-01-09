#include "jcpp/lang/JAutoCloseable.h"

namespace jcpp{
    namespace lang{
        class JAutoCloseableClass : public jcpp::lang::JClass{
            public:
                JAutoCloseableClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.lang.AutoCloseable");
                    this->name=new JString("java.lang.AutoCloseable");
                    this->simpleName=new JString("AutoCloseable");
                    this->bIsInterface=true;
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JInterface::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JAutoCloseable::getClazz(){
            if (clazz==null){
                clazz=new JAutoCloseableClass();
            }
            return clazz;
        }

        JAutoCloseable::~JAutoCloseable(){
        }
    }
}
