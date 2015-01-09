#ifndef JCPP_RMI_SERVER_CONNECTION_SERIALIZATION_JDEFAULTNOTSERIALIZABLEOBJECTHANDLER_H
#define JCPP_RMI_SERVER_CONNECTION_SERIALIZATION_JDEFAULTNOTSERIALIZABLEOBJECTHANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/connection/serialization/JINotSerializableObjectHandler.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                namespace serialization{
                // @Class(canonicalName="jcpp.rmi.server.connection.serialization.DefaultNotSerializableObjectHandler", simpleName="DefaultNotSerializableObjectHandler");
                    class JCPP_EXPORT JDefaultNotSerializableObjectHandler : public JObject, JINotSerializableObjectHandler{
                    public:
                        JDefaultNotSerializableObjectHandler();

                        static JClass* getClazz();

                        virtual JObject* handleNotSerializableObject(JObject* obj);

                        virtual ~JDefaultNotSerializableObjectHandler();
                    };
                }
            }
        }
    }
}

#endif
