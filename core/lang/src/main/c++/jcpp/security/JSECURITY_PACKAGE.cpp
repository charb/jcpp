#include "jcpp/security/JSECURITY_PACKAGE.h"
#include "jcpp/JCPP_PACKAGE.h"
#include "jcpp/security/JSecureClassLoader.h"

using namespace jcpp;

namespace jcpp{
    namespace security{
        JSECURITY_PACKAGE::JSECURITY_PACKAGE():JPackage(new JString("jcpp.security"),JPackage::getClazz()){//better class
            addClass(JSecureClassLoader::getClazz());
        }

        JPackage* JSECURITY_PACKAGE::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        JList* JSECURITY_PACKAGE::getPackages(){
            return packages;
        }

        static JSECURITY_PACKAGE* jcpp=null;

        JSECURITY_PACKAGE* JSECURITY_PACKAGE::getPackage(){
            if (jcpp==null){
                jcpp=new JSECURITY_PACKAGE();
            }
            return jcpp;
        }

        JSECURITY_PACKAGE::~JSECURITY_PACKAGE(){
        }
    }
}

