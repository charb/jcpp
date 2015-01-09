#include "jcpp/rmi/server/transport/JSocketConnection.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/rmi/server/transport/JConnections.h"
#include "jcpp/rmi/server/transport/JTransport.h"
#include "jcpp/rmi/server/gateway/JGatewaySocketFactory.h"
#include "jcpp/rmi/server/gateway/JIGatewaySocket.h"

using namespace jcpp::rmi::server::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{


                JSocketConnection::JSocketConnection(JRoute* route, JConnections* connections, JGatewayConfiguration* gatewayConfiguration) : JConnection(getClazz(),route, connections, gatewayConfiguration){
                    this->socket = JGatewaySocketFactory::createSocket(route, connections->getTransport()->getTransportConfiguration()->getGatewayConfiguration());
                    this->socket->setSoTimeout(connections->getTransport()->getTransportConfiguration()->getSocketTimeout()->get());
                    this->socket->setTcpNoDelay(true);
                    this->socket->setKeepAlive(true);
                }

                JSocketConnection::JSocketConnection(JSocket* socket, JTransport* transport, JGatewayConfiguration* gatewayConfiguration) : JConnection(getClazz(),transport, gatewayConfiguration){
                    this->socket = socket;
                }

                void JSocketConnection::setSoTimeout(jint timeout){
                    socket->setSoTimeout(timeout);
                }

                jbool JSocketConnection::isReusable() {
                    return (dynamic_cast<JIGatewaySocket*>(socket))->isReusable();
                }

                JSocket* JSocketConnection::getSocket() {
                    return socket;
                }

                void JSocketConnection::killInternal(){
                    socket->close();
                }

                jbool JSocketConnection::isSocketClosed() {
                    return socket->isClosed();
                }

                JSocket* JSocketConnection::getSocketInternal() {
                    return socket;
                }

                JOutputStream* JSocketConnection::getOuputStreamInternal(){
                    return socket->getOutputStream();
                }

                JInputStream* JSocketConnection::getInputStreamInternal(){
                    return socket->getInputStream();
                }
                
                JSocketConnection::~JSocketConnection(){
                }
            }
        }
    }
}

