#ifndef JCPP_IO_JSERIALCALLBACKCONTEXT_H
#define JCPP_IO_JSERIALCALLBACKCONTEXT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JObjectStreamClass;

        //@Class(canonicalName="java.io.SerialCallbackContext", simpleName="SerialCallbackContext");
        class JCPP_EXPORT JSerialCallbackContext : public JObject{
        private:
            JObject* curObj;
            JObjectStreamClass* curDesc;

        public:
            JSerialCallbackContext(JObject* obj,JObjectStreamClass* desc);

            static jcpp::lang::JClass* getClazz();

            virtual JObject* getObj();

            virtual JObjectStreamClass* getDesc();
        };
    }
}

#endif
