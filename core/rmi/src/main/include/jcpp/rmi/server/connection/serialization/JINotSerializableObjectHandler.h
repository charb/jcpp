#ifndef JCPP_RMI_SERVER_CONNECTION_SERIALIZATION_JINOTSERIALIZABLEOBJECTHANDLER_H
#define JCPP_RMI_SERVER_CONNECTION_SERIALIZATION_JINOTSERIALIZABLEOBJECTHANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                namespace serialization{
                // @Class(canonicalName="jcpp.rmi.server.connection.serialization.INotSerializableObjectHandler", simpleName="INotSerializableObjectHandler");
                    class JCPP_EXPORT JINotSerializableObjectHandler : public JInterface{
                    public:
                        static JClass* getClazz();

                        virtual JObject* handleNotSerializableObject(JObject* obj)=0;

                        virtual ~JINotSerializableObjectHandler();
                    };
                }
            }
        }
    }
}

#endif
