#ifndef JCPP_SECURITY_JSECURECLASSLOADER_H
#define JCPP_SECURITY_JSECURECLASSLOADER_H

#include "jcpp/lang/JClassLoader.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace security{
        class JCPP_EXPORT JSecureClassLoader : public JClassLoader{
            protected:
                JSecureClassLoader(jcpp::lang::JClass* _class,JClassLoader* parent);

            public:
                static jcpp::lang::JClass* getClazz();

                virtual ~JSecureClassLoader();
        };
    }
}

#endif
