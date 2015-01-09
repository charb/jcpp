#ifndef JCPP_LANG_JREADABLE_H
#define JCPP_LANG_JREADABLE_H

#include "jcpp/lang/JInterface.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JReadable : public JInterface  {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual ~JReadable();
        };
    }
}

#endif
