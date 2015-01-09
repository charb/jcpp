#ifndef JCPP_LANG_REFLECT_JPACKAGELOADER_H
#define JCPP_LANG_REFLECT_JPACKAGELOADER_H

#include "jcpp/lang/reflect/JPackage.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JPackageLoader{
                public:
                    virtual JPackage* getPackage() = 0;
                    virtual ~JPackageLoader() {
                    }
            };
        }
    }
}

#endif
