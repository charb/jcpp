#ifndef JCPP_RMI_SREVER_TRANSPORT_JSOCKET_CONNECTION_H
#define JCPP_RMI_SREVER_TRANSPORT_JSOCKET_CONNECTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/rmi/server/transport/JConnection.h"
#include "jcpp/rmi/server/transport/JConnections.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"

using namespace jcpp::rmi::server::gateway;
using namespace jcpp::net;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
                class JConnections;
                class JTransport;

                // @Class(canonicalName="jcpp.rmi.server.transport.SocketConnection", simpleName="SocketConnection");
                class JCPP_EXPORT JSocketConnection : public JConnection{
                    protected:
                        JSocket* socket;
                        virtual void killInternal();
                        virtual jbool isSocketClosed();   
                        virtual JSocket* getSocketInternal();
                        virtual JOutputStream* getOuputStreamInternal();
                        virtual JInputStream* getInputStreamInternal();

                    public:
                        JSocketConnection(JRoute* route, JConnections* connections,JGatewayConfiguration* gatewayConfiguration);
                        
                        JSocketConnection(JSocket* socket, JTransport* transport,JGatewayConfiguration* gatewayConfiguration);
                        
                        static JClass* getClazz();
                        
                        virtual void setSoTimeout(jint timeout);

                        virtual jbool isReusable();

                        virtual JSocket* getSocket();
                        
                        virtual ~JSocketConnection();
                };
            }
        }
    }
}


#endif
