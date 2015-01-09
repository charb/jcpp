#ifndef JCPP_RMI_SERVER_CONNECTION_SERIALIZATION_JNULLNOTSERIALIZABLEOBJECTHANDLER_H
#define JCPP_RMI_SERVER_CONNECTION_SERIALIZATION_JNULLNOTSERIALIZABLEOBJECTHANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/connection/serialization/JINotSerializableObjectHandler.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                namespace serialization{
                // @Class(canonicalName="jcpp.rmi.server.connection.serialization.NullNotSerializableObjectHandler", simpleName="NullNotSerializableObjectHandler");
                    class JCPP_EXPORT JNullNotSerializableObjectHandler : public JObject, JINotSerializableObjectHandler{
                    public:
                        JNullNotSerializableObjectHandler();

                        static JClass* getClazz();

                        virtual JObject* handleNotSerializableObject(JObject* obj);

                        virtual ~JNullNotSerializableObjectHandler();
                    };
                }
            }
        }
    }
}

#endif
