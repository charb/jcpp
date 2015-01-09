#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYINPUTSTREAM_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYINPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/rmi/server/gateway/JRoute.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewayInputStream", simpleName="GatewayInputStream");
                class JCPP_EXPORT JGatewayInputStream : public JObjectInputStream{
                protected:
                    JRoute* route;

                public:
                    JGatewayInputStream(JInputStream* in);

                    static JClass* getClazz();

                    virtual JRoute* getRoute();

                    virtual ~JGatewayInputStream();
                };
            }
        }
    }
}

#endif
