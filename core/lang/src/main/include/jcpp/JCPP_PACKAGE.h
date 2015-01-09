#ifndef JCPP_JCPP_PACKAGE_H
#define JCPP_JCPP_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    class JCPP_EXPORT JCPP_PACKAGE : public JPackage{
    protected:
        JCPP_PACKAGE();

    public:
    	static JCPP_PACKAGE* getPackage();

        virtual JPackage* getSuperPackage();

        virtual JList* getPackages();

        virtual ~JCPP_PACKAGE();
    };
}

#endif
