#ifndef JCPP_LANG_JERROR_H
#define JCPP_LANG_JERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JError : public JThrowable {
        protected:
            JError(jcpp::lang::JClass* _class);
            JError(jcpp::lang::JClass* _class, JThrowable* cause);

        public:
            JError();

            JError(JString* message);

            JError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JError();
        };
    }
}

#endif
