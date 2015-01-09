#ifndef JCPP_LANG_JEXCEPTION_H
#define JCPP_LANG_JEXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JException: public JThrowable {
        protected:
            JException(jcpp::lang::JClass* _class);

        public:
            JException();

            JException(JString* message);

            JException(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JException();
        };
    }
}


#endif
