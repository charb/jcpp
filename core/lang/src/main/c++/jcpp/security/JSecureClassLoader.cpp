#include "jcpp/security/JSecureClassLoader.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace security{
        class JSecureClassLoaderClass : public jcpp::lang::JClass{
            public:
                JSecureClassLoaderClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.security.SecureClassLoader");
                    this->name=new JString("java.security.SecureClassLoader");
                    this->simpleName=new JString("SecureClassLoader");
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JClassLoader::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JSecureClassLoader::getClazz(){
            if (clazz==null){
                clazz=new JSecureClassLoaderClass();
            }
            return clazz;
        }

        JSecureClassLoader::JSecureClassLoader(jcpp::lang::JClass* _class,JClassLoader* parent):JClassLoader(_class,parent){
        }

        JSecureClassLoader::~JSecureClassLoader(){
        }
    }
}

