#include "jcpp/JCPPPackageLoader.h"
#include "jcpp/JCPP_PACKAGE.h"

namespace jcpp{
    JCPPPackageLoader::JCPPPackageLoader(){
    }

    JPackage* JCPPPackageLoader::getPackage(){
        return JCPP_PACKAGE::getPackage();
    }

    JCPPPackageLoader::~JCPPPackageLoader(){
    }
}

static JPackageLoader* jcppPackageLoader = null;

extern "C" JCPP_EXPORT JPackageLoader* getPackageLoader(){
    if (jcppPackageLoader==null){
        jcppPackageLoader=new jcpp::JCPPPackageLoader();
    }
    return jcppPackageLoader;
}
