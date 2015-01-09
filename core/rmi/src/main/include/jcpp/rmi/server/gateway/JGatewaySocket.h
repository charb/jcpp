#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYSOCKET_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYSOCKET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/net/JInetAddress.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/rmi/server/gateway/JIGatewaySocket.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"
#include "jcpp/rmi/server/gateway/JGatewayCompressionOutputStream.h"
#include "jcpp/rmi/server/gateway/JGatewayCompressionInputStream.h"

using namespace jcpp::io;
using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewaySocket", simpleName="GatewaySocket");
                class JCPP_EXPORT JGatewaySocket : public JSocket, public JIGatewaySocket{
                    protected:
                        JSocket* socket;
                        JInputStream* input;
                        JOutputStream* output;
                        jbool bSendSocket;
                        JRoute* route;
                        JGatewayConfiguration* gatewayConfiguration;
                        void setSocketSetting();

                    public:
                        JGatewaySocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration);

                        JGatewaySocket(JSocket* socket,JInputStream* in,JGatewayConfiguration* gatewayConfiguration);

                        static JClass* getClazz();

                        virtual JRoute* getRoute();

                        virtual jbool isReusable();

                        virtual JInetAddress* getInetAddress();

                        virtual JInetAddress* getLocalAddress();

                        virtual jint getPort();

                        virtual jint getLocalPort();

                        virtual JInputStream* getInputStream();

                        virtual JOutputStream* getOutputStream();

                        virtual void setTcpNoDelay(jbool on);

                        virtual jbool getTcpNoDelay();

                        virtual void setSoLinger(jbool on, jint linger);

                        virtual jint getSoLinger();

                        virtual void setOOBInline(jbool on);

                        virtual jbool getOOBInline();

                        virtual void setSoTimeout(jint s);

                        virtual jint getSoTimeout();

                        virtual void setSendBufferSize(jint size);

                        virtual jint getSendBufferSize();

                        virtual void setReceiveBufferSize(jint size);

                        virtual jint getReceiveBufferSize();

                        virtual void setKeepAlive(jbool on);

                        virtual jbool getKeepAlive();

                        virtual void setReuseAddress(jbool on);

                        virtual jbool getReuseAddress();

                        virtual void close();

                        virtual jbool isClosed();

                        virtual JString* toString();

                        virtual ~JGatewaySocket();
                };
            }
        }
    }
}

#endif
