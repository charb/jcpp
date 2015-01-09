#ifndef JCPP_LANG_JUNSUPPORTEDOPERATIONEXCEPTION_H
#define JCPP_LANG_JUNSUPPORTEDOPERATIONEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JUnsupportedOperationException : public JRuntimeException{
        protected:
            JUnsupportedOperationException(jcpp::lang::JClass* _class);
        public:
            JUnsupportedOperationException();

            JUnsupportedOperationException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JUnsupportedOperationException();
        };
    }
}

#endif
