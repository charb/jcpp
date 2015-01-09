#include "jcpp/rmi/server/gateway/JGatewaySocket.h"
#include "jcpp/net/JInetSocketAddress.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{


                JGatewaySocket::JGatewaySocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration):JSocket(getClazz()){
                    JAddress* address = route->popAddress();
                    this->gatewayConfiguration = gatewayConfiguration;
                    JInetSocketAddress* socketAddress = new JInetSocketAddress(address->getHostName(), address->getPort());
                    this->socket = new JSocket();
                    socket->connect(socketAddress,gatewayConfiguration->getConnectionTimeout()->get());
                    this->output = new JGatewayCompressionOutputStream(socket->getOutputStream(), route);
                    this->input = socket->getInputStream();
                    this->bSendSocket = true;
                    this->route = route;
                    setSocketSetting();
                }

                JGatewaySocket::JGatewaySocket(JSocket* socket,JInputStream* in,JGatewayConfiguration* gatewayConfiguration):JSocket(getClazz()){
                    this->socket = socket;
                    this->gatewayConfiguration = gatewayConfiguration;
                    this->output = socket->getOutputStream();
                    this->input = new JGatewayCompressionInputStream(in, gatewayConfiguration);
                    this->bSendSocket = false;
                    this->route = ((JGatewayCompressionInputStream*) input)->getRoute();
                    this->input = input;
                    setSocketSetting();
                }

                JRoute* JGatewaySocket::getRoute(){
                    return route;
                }

                jbool JGatewaySocket::isReusable(){
                    return true;
                }

                JInetAddress* JGatewaySocket::getInetAddress(){
                    return socket->getInetAddress();
                }

                JInetAddress* JGatewaySocket::getLocalAddress(){
                    return socket->getLocalAddress();
                }

                jint JGatewaySocket::getPort(){
                    return socket->getPort();
                }

                jint JGatewaySocket::getLocalPort(){
                    return socket->getLocalPort();
                }

                JInputStream* JGatewaySocket::getInputStream(){
                    return input;
                }

                JOutputStream* JGatewaySocket::getOutputStream(){
                    return output;
                }

                void JGatewaySocket::setTcpNoDelay(jbool on){
                    socket->setTcpNoDelay(on);
                }

                jbool JGatewaySocket::getTcpNoDelay(){
                    return socket->getTcpNoDelay();
                }

                void JGatewaySocket::setSoLinger(jbool on, jint linger){
                    socket->setSoLinger(on,linger);
                }

                jint JGatewaySocket::getSoLinger(){
                    return socket->getSoLinger();
                }

                void JGatewaySocket::setOOBInline(jbool on){
                    socket->setOOBInline(on);
                }

                jbool JGatewaySocket::getOOBInline(){
                    return socket->getOOBInline();
                }

                void JGatewaySocket::setSoTimeout(jint s){
                    socket->setSoTimeout(s);
                }

                jint JGatewaySocket::getSoTimeout(){
                    return socket->getSoTimeout();
                }

                void JGatewaySocket::setSendBufferSize(jint size){
                    socket->setSendBufferSize(size);
                }

                jint JGatewaySocket::getSendBufferSize(){
                    return socket->getSendBufferSize();
                }

                void JGatewaySocket::setReceiveBufferSize(jint size){
                    socket->setReceiveBufferSize(size);
                }

                jint JGatewaySocket::getReceiveBufferSize(){
                    return socket->getReceiveBufferSize();
                }

                void JGatewaySocket::setKeepAlive(jbool on){
                    socket->setKeepAlive(on);
                }

                jbool JGatewaySocket::getKeepAlive(){
                    return socket->getKeepAlive();
                }

                void JGatewaySocket::setReuseAddress(jbool on){
                    socket->setReuseAddress(on);
                }

                jbool JGatewaySocket::getReuseAddress(){
                    return socket->getReuseAddress();
                }

                void JGatewaySocket::close(){
                    output->close();
                    input->close();
                    socket->close();
                    JSocket::close();
                }

                jbool JGatewaySocket::isClosed(){
                    return socket->isClosed();
                }

                JString* JGatewaySocket::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("GatewaySocket")
                           ->append(bSendSocket ? "(SendSocket)" : "(ReceiveSocket)")
                           ->append("[socket:")->append(socket->toString())->append("]");
                    return builder->toString();
                }

                void JGatewaySocket::setSocketSetting(){
                    socket->setSoTimeout(gatewayConfiguration->getReadTimeout()->get());
                }

                JGatewaySocket::~JGatewaySocket(){
                }
            }
        }
    }
}

