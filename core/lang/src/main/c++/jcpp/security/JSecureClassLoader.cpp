#include "jcpp/security/JSecureClassLoader.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace security{

        JSecureClassLoader::JSecureClassLoader(jcpp::lang::JClass* _class,JClassLoader* parent):JClassLoader(_class,parent){
        }

        JSecureClassLoader::~JSecureClassLoader(){
        }
    }
}

