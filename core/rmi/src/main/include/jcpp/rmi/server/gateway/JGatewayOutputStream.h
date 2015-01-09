#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYOUTPUTSTREAM_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYOUTPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/rmi/server/gateway/JRoute.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewayOutputStream", simpleName="GatewayOutputStream");
                class JCPP_EXPORT JGatewayOutputStream : public JObjectOutputStream{
                protected:
                    JRoute* route;

                public:
                    JGatewayOutputStream(JOutputStream* out,JRoute* route);

                    static JClass* getClazz();

                    virtual JRoute* getRoute();

                    virtual ~JGatewayOutputStream();
                };
            }
        }
    }
}


#endif
