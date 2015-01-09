#include "jcpp/JCPP_PACKAGE.h"
#include "jcpp/io/JIO_PACKAGE.h"
#include "jcpp/util/JUTIL_PACKAGE.h"
#include "jcpp/lang/JLANG_PACKAGE.h"
#include "jcpp/net/JNET_PACKAGE.h"
#include "jcpp/security/JSECURITY_PACKAGE.h"
#include "jcpp/nio/JNIO_PACKAGE.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::lang;
using namespace jcpp::net;
using namespace jcpp::security;
using namespace jcpp::nio;

namespace jcpp{
    JCPP_PACKAGE::JCPP_PACKAGE():JPackage(new JString("java"),JPackage::getClazz()){
    }

    JPackage* JCPP_PACKAGE::getSuperPackage(){
        return null;
    }

    JList* JCPP_PACKAGE::getPackages(){
        if (packages->size()==0){
            addPackage(JIO_PACKAGE::getPackage());
            addPackage(JLANG_PACKAGE::getPackage());
            addPackage(JNET_PACKAGE::getPackage());
            addPackage(JSECURITY_PACKAGE::getPackage());
            addPackage(JUTIL_PACKAGE::getPackage());
            addPackage(JNIO_PACKAGE::getPackage());
        }
        return packages;
    }

    static JCPP_PACKAGE* jcpp=null;

    JCPP_PACKAGE* JCPP_PACKAGE::getPackage(){
        if (jcpp==null){
            jcpp=new JCPP_PACKAGE();
        }
        return jcpp;
    }

    JCPP_PACKAGE::~JCPP_PACKAGE(){
    }
}
