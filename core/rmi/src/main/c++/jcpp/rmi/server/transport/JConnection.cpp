#include "jcpp/rmi/server/transport/JConnection.h"
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

                JConnection::JConnection(JClass* _class,JRoute* route, JConnections* connections,JGatewayConfiguration* gatewayConfiguration):JObject(_class){
                    this->lastUsed=0;
                    this->out=null;
                    this->in=null;
                    this->opened=false;
                    this->transport=null;
                    this->route=route;
                    this->connections=connections;
                    this->gatewayConfiguration=gatewayConfiguration;
                }

                JConnection::JConnection(JClass* _class,JTransport* transport, JGatewayConfiguration* gatewayConfiguration):JObject(_class){
                    this->out=null;
                    this->in=null;
                    this->opened=false;
                    this->route=null;
                    this->transport=transport;
                    this->gatewayConfiguration=gatewayConfiguration;
                    this->lastUsed=0;
                    this->connections=null;
                }

                void JConnection::free(){
                    if (connections!=null){
                        if (isReusable()){
                            connections->free(this);
                        }else{
                            kill();
                        }
                    }
                }

                void JConnection::kill(){
                    if (connections!=null){
                        connections->kill(this);
                    }
                    killInternal();
                }

                jbool JConnection::openConnection(){
                    if (!opened){
                        sendConnectionHeader();
                        out->flush();

                        if (isReusable()){
                            jint oldTimeout=getSocketInternal()->getSoTimeout();
                            if (connections==null){
                                setSoTimeout(transport->getTransportConfiguration()->getPingTimeout()->get());
                            }else{
                                setSoTimeout(connections->getTransport()->getTransportConfiguration()->getPingTimeout()->get());
                            }
                            jbool b=readOk();
                            setSoTimeout(oldTimeout);
                            return b;
                        }
                    }
                    return true;
                }

                void JConnection::startCall(){
                    getOutputStream();
                    out->writeByte(JTransportConfiguration::MSG_TYPE_CALL);
                }

                void JConnection::finishCall(){
                    getOutputStream();
                    out->flush();
                }

                void JConnection::sendOk(){
                    getOutputStream();
                    out->writeByte(JTransportConfiguration::MSG_TYPE_OK);
                    if (isReusable()){
                        out->flush();
                    }
                }

                jbool JConnection::readOk(){
                    getInputStream();
                    jbyte okByte=in->readByte();
                    if (okByte!= JTransportConfiguration::MSG_TYPE_OK){
                        return false;
                    }
                    return true;
                }

                jbool JConnection::isDead(){
                    jbool isDead=false;
                    jint oldTimeout=getSocketInternal()->getSoTimeout();
                    try{
                        sendPing();
                        if (connections==null){
                            setSoTimeout(transport->getTransportConfiguration()->getPingTimeout()->get());
                        } else {
                            setSoTimeout(connections->getTransport()->getTransportConfiguration()->getPingTimeout()->get());
                        }
                        if (!readOk()) {
                            isDead = true;
                        }
                    }catch(JIOException* e){
                        isDead=true;
                    }

                    if (isDead && !isSocketClosed()){
                        killInternal();
                    }else{
                        setSoTimeout(oldTimeout);
                    }
                    return isDead;
                }

                JDataOutputStream* JConnection::getOutputStream(){
                    if (out==null){
                        JOutputStream* outputStream=getOuputStreamInternal();
                        out=new JDataOutputStream(outputStream);//TODO implemenet bufferedoutputstream
                    }
                    return out;
                }

                JDataInputStream* JConnection::getInputStream(){
                    if (in==null){
                        JInputStream* inputStream=getInputStreamInternal();
                        in=new JDataInputStream(inputStream);
                    }
                    return in;
                }

                JGatewayConfiguration* JConnection::getGatewayConfiguration() {
                    return gatewayConfiguration;
                }

                void JConnection::setLastUsed(){
                    this->lastUsed=JSystem::currentTimeMillis();
                }

                jbool JConnection::isReusable(){
                    return true;
                }
                
                void JConnection::setSoTimeout(jint timeout){
                }

                jlong JConnection::getLastUsed(){
                    return lastUsed;
                }

                JConnections* JConnection::getConnections(){
                    return connections;
                }

                JString* JConnection::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Connection[")
                           ->append(connections)
                           ->append(",")
                           ->append(getSocketInternal())
                           ->append("]");
                    return builder->toString();
                }

                void JConnection::sendConnectionHeader(){
                    opened = true;
                    getOutputStream();
                    out->writeInt(JTransportConfiguration::MAGIC_NUMBER);
                    connections->getTransport()->getLocalEndPoint()->write(out);
                }

                void JConnection::sendPing(){
                    out->writeByte(JTransportConfiguration::MSG_TYPE_PING);
                    out->flush();
                }

                JConnection::~JConnection(){
                }
            }
        }
    }
}

