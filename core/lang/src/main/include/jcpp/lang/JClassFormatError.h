#ifndef JCPP_LANG_JCLASS_FORMAT_H
#define JCPP_LANG_JCLASS_FORMAT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JClassFormatError : public JLinkageError {
        protected:
            JClassFormatError(jcpp::lang::JClass* _class);

        public:
            JClassFormatError();

            JClassFormatError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JClassFormatError();
        };
    }
}

#endif
