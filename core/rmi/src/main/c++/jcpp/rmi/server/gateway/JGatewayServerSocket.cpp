#include "jcpp/rmi/server/gateway/JGatewayServerSocket.h"
#include "jcpp/rmi/server/gateway/JGatewaySocket.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/net/JInetAddress.h"

using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{

                JGatewayServerSocket::JGatewayServerSocket(JString* host, jint port,JGatewayConfiguration* gatewayConfiguration):JServerSocket(getClazz(),port, gatewayConfiguration->getBackLog()->get(), JInetAddress::getByName(host)){
                    this->gatewayConfiguration=gatewayConfiguration;
                }

                JSocket* JGatewayServerSocket::accept(){
                    JSocket* socket=JServerSocket::accept();
                    socket->setReceiveBufferSize(gatewayConfiguration->getReceiveBufferSize()->get());
                    socket->setSendBufferSize(gatewayConfiguration->getSendBufferSize()->get());
                    socket->setSoTimeout(gatewayConfiguration->getReadTimeout()->get());
                    return new JGatewaySocket(socket,socket->getInputStream(),gatewayConfiguration);//TODO handle HTTP
                }

                JString* JGatewayServerSocket::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("GatewayServerSocket[ServerSocket:")
                           ->append(JServerSocket::toString())
                           ->append("]");
                    return builder->toString();
                }

                JGatewayServerSocket::~JGatewayServerSocket(){
                }
            }
        }
    }
}


