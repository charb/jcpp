#ifndef JCPP_LANG_JUNSUPPORTED_CLASS_VERSION_ERROR_H
#define JCPP_LANG_JUNSUPPORTED_CLASS_VERSION_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClassFormatError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JUnsupportedClassVersionError : public jcpp::lang::JClassFormatError {
        protected:
            JUnsupportedClassVersionError(jcpp::lang::JClass* _class);

        public:
            JUnsupportedClassVersionError();

            JUnsupportedClassVersionError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JUnsupportedClassVersionError();
        };
    }
}

#endif
