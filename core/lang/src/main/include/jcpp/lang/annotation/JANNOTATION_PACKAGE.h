#ifndef JCPP_LANG_ANNOTATION_JANNOTATION_PACKAGE_H
#define JCPP_LANG_ANNOTATION_JANNOTATION_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_EXPORT JANNOTATION_PACKAGE : public JPackage{
            protected:
                JANNOTATION_PACKAGE();

            public:
                static JANNOTATION_PACKAGE* getPackage();

                virtual JPackage* getSuperPackage();

                virtual JList* getPackages();

                virtual ~JANNOTATION_PACKAGE();
            };
        }
    }
}


#endif
