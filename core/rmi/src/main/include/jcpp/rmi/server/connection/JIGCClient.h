#ifndef JCPP_RMI_SERVER_CONNECTION_JIGCCLIENT_H
#define JCPP_RMI_SERVER_CONNECTION_JIGCCLIENT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IGCClient", simpleName="IGCClient");
                class JCPP_EXPORT JIGCClient : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JPrimitiveObjectArray* getEndPoints()=0;

                    virtual ~JIGCClient();
                };
            }
        }
    }
}

#endif
