#ifndef JCPP_UTIL_JUTIL_PACKAGE_H
#define JCPP_UTIL_JUTIL_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JUTIL_PACKAGE : public JPackage{
        protected:
            JUTIL_PACKAGE();

        public:
            static JUTIL_PACKAGE* getPackage();

            virtual JPackage* getSuperPackage();

            virtual JList* getPackages();

            virtual ~JUTIL_PACKAGE();
        };
    }
}

#endif
