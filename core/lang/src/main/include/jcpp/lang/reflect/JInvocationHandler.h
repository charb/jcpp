#ifndef JCPP_LANG_REFLECT_JINVOCATIONHANDLER_H
#define JCPP_LANG_REFLECT_JINVOCATIONHANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JCPP_EXPORT JInvocationHandler : public JInterface{
            public:
                static jcpp::lang::JClass* getClazz();

                virtual JObject* invoke(JObject* proxy, JMethod* method, JList* args) = 0;

                virtual ~JInvocationHandler();
            };
        }
    }
}
#endif
