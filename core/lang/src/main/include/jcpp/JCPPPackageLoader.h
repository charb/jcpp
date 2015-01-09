#ifndef JCPP_JCPP_PACKAGE_LOADERH
#define JCPP_JCPP_PACKAGE_LOADERH

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/lang/reflect/JPackageLoader.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    class JCPP_EXPORT JCPPPackageLoader : public JPackageLoader{
    public:
    	JCPPPackageLoader();

    	virtual JPackage* getPackage();

        virtual ~JCPPPackageLoader();
    };
}

#endif
