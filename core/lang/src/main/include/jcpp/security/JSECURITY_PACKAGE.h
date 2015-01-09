#ifndef JCPP_JSECURITY_PACKAGE_H
#define JCPP_JSECURITY_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace security{
        class JCPP_EXPORT JSECURITY_PACKAGE : public JPackage{
        protected:
            JSECURITY_PACKAGE();

        public:
            JPackage* getSuperPackage();

            JList* getPackages();

            static JSECURITY_PACKAGE* getPackage();

            virtual ~JSECURITY_PACKAGE();
        };
    }
}

#endif
