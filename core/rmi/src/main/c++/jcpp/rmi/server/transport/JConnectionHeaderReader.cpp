#include "jcpp/rmi/server/transport/JConnectionHeaderReader.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/rmi/server/transport/JConnection.h"
#include "jcpp/rmi/server/transport/JSocketConnection.h"
#include "jcpp/rmi/server/transport/JITransportDispatcher.h"
#include "jcpp/rmi/server/gateway/JIGatewaySocket.h"
#include "jcpp/io/JEOFException.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{

                JConnectionHeaderReader::JConnectionHeaderReader(JSocket* socket, JTransport* transport):JObject(getClazz()){
                    this->socket=socket;
                    this->transport=transport;
                }

                void JConnectionHeaderReader::unexport(){
                    if (socket!=null){
                        socket->close();
                    }
                }

                void JConnectionHeaderReader::run(){
                    JString* oldName = JThread::currentThread()->getName();
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Connection Header Reader Thread - ")->append(socket);
                    JThread::currentThread()->setName(builder->toString());
                    JConnection* connection = null;
                    JThrowable* thrown=null;
                    try{
                        JIGatewaySocket* s=dynamic_cast<JIGatewaySocket*>(socket);
                        JDataInputStream* in = new JDataInputStream(socket->getInputStream());
                        jint magicNumber = in->readInt();
                        if (magicNumber != JTransportConfiguration::MAGIC_NUMBER) {
                            throw new JEOFException();
                        }
                        JEndPoint* remoteEndPoint = new JEndPoint(in);
                        connection = new JSocketConnection(socket, transport, transport->getTransportConfiguration()->getGatewayConfiguration());

                        if (connection->isReusable()) {
                            connection->sendOk();
                        }
                        do{
                            jbyte msgType = in->readByte();
                            if (msgType == JTransportConfiguration::MSG_TYPE_PING) {
                                connection->sendOk();
                                if (!connection->isReusable()) {
                                    connection->getOutputStream()->flush();
                                }

                            } else if (msgType == JTransportConfiguration::MSG_TYPE_CALL) {
                                transport->getTransportDispatcher()->dispatch(remoteEndPoint, transport->getLocalEndPoint(), connection);

                                if (!connection->isReusable()) {
                                    connection->sendOk();
                                }
                                connection->getOutputStream()->flush();
                            } else {
                                throw new JEOFException(new JString("Unknown message type"));
                            }

                        } while (!socket->isClosed() && s->isReusable());
                
                    }catch(JThrowable* th){
                        th->printStackTrace();
                        thrown=th;
                    }


                    if (connection != null) {
                        connection->kill();
                    }
                    transport->remove(this);
                    JThread::currentThread()->setName(oldName);
                    
                    if (thrown!=null){
                        throw thrown;
                    }
                }

                JConnectionHeaderReader::~JConnectionHeaderReader(){
                }
            }
        }
    }
}
