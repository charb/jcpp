#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYCOMPRESSIONOUTPUTSTREAM_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYCOMPRESSIONOUTPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFilterOutputStream.h"
#include "jcpp/rmi/server/gateway/JGatewayOutputStream.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewayCompressionOutputStream", simpleName="GatewayCompressionOutputStream");
                class JCPP_EXPORT JGatewayCompressionOutputStream : public JFilterOutputStream{
                    protected:
                        JGatewayOutputStream* gatewayOutputStream;

                    public:
                        JGatewayCompressionOutputStream(JOutputStream* o,JRoute* route);

                        static JClass* getClazz();

                        virtual JRoute* getRoute();

                        virtual void close();

                        virtual ~JGatewayCompressionOutputStream();
                };
            }
        }
    }
}

#endif
