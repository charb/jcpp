#ifndef JCPP_LANG_JPRIMITIVEVOID_H
#define JCPP_LANG_JPRIMITIVEVOID_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveVoid : public JObject{
        public:
                static jcpp::lang::JClass* getClazz();

                virtual ~JPrimitiveVoid();
        };
    }
}

#endif
