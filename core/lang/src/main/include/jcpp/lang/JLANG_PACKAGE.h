#ifndef JCPP_LANG_JLANG_PACKAGE_H
#define JCPP_LANG_JLANG_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JLANG_PACKAGE : public JPackage{
        protected:
            JLANG_PACKAGE();

        public:
            static JLANG_PACKAGE* getPackage();

            virtual JPackage* getSuperPackage();

            virtual JList* getPackages();

            virtual ~JLANG_PACKAGE();
        };
    }
}
#endif
