#ifndef JCPP_LANG_REFLECT_JREFLECT_PACKAGE_H
#define JCPP_LANG_REFLECT_JREFLECT_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_EXPORT JREFLECT_PACKAGE : public JPackage{
            protected:
                JREFLECT_PACKAGE();

            public:
                static JREFLECT_PACKAGE* getPackage();

                virtual JPackage* getSuperPackage();

                virtual JList* getPackages();

                virtual ~JREFLECT_PACKAGE();
            };
        }
    }
}


#endif
