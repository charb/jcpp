#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYCOMPRESSIONINPUTSTREAM_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYCOMPRESSIONINPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFilterInputStream.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"
#include "jcpp/rmi/server/gateway/JGatewayInputStream.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewayCompressionInputStream", simpleName="GatewayCompressionInputStream");
                class JCPP_EXPORT JGatewayCompressionInputStream : public JFilterInputStream{
                    protected:
                        JGatewayInputStream* gatewayInputStream;

                    public:
                        JGatewayCompressionInputStream(JInputStream* i,JGatewayConfiguration* gatewayConfiguration);

                        static JClass* getClazz();

                        virtual JRoute* getRoute();

                        virtual ~JGatewayCompressionInputStream();
                };
            }
        }
    }
}

#endif
