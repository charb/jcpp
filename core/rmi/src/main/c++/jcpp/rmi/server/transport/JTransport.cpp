#include "jcpp/rmi/server/transport/JTransport.h"
#include "jcpp/rmi/server/transport/JConnectionHeaderReader.h"
#include "jcpp/rmi/server/gateway/JGatewaySocketFactory.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{


                JTransport::JTransport(JEndPoint* localEndPoint,JITransportRouter* transportRouter,JITransportDispatcher* transportDispatcher,JExecutorService* executorService,JScheduledExecutorService* scheduledExecutorService,JTransportConfiguration* transportConfiguration) : JObject(getClazz()){
                    this->localEndPoint=localEndPoint;
                    this->transportRouter=transportRouter;
                    this->transportDispatcher=transportDispatcher;
                    this->scheduledExecutorService=scheduledExecutorService;
                    this->remoteConnectionsMap=new JHashMap();
                    this->connectionReaders=JCollections::synchronizedSet(new JHashSet());
                    this->executorService=executorService;
                    this->transportConfiguration=transportConfiguration;
                }

                JConnections* JTransport::getConnections(JEndPoint* remoteEndPoint){
                    JConnections* connections=null;
                    synchronized(this,{
                        connections=dynamic_cast<JConnections*>(remoteConnectionsMap->get(remoteEndPoint));
                        if (connections==null){
                            connections=new JConnections(remoteEndPoint,this);
                            remoteConnectionsMap->put(remoteEndPoint,connections);
                        }
                        return connections;
                    })
                }

                JEndPoint* JTransport::getLocalEndPoint(){
                    return localEndPoint;
                }

                JScheduledExecutorService* JTransport::getScheduledExecutorService(){
                    return scheduledExecutorService;
                }

                JITransportDispatcher* JTransport::getTransportDispatcher(){
                    return transportDispatcher;
                }

                JITransportRouter* JTransport::getTransportRouter(){
                    return transportRouter;
                }

                JTransportConfiguration* JTransport::getTransportConfiguration(){
                    return transportConfiguration;
                }

                void JTransport::startExport(){
                    serverSocket = JGatewaySocketFactory::createServerSocket(localEndPoint->getAddress()->getHostName(),localEndPoint->getAddress()->getPort(), transportConfiguration->getGatewayConfiguration());
                    localEndPoint->getAddress()->setPort(serverSocket->getLocalPort());
                    future=executorService->submit(this);
                }

                void JTransport::run(){
                    while ((serverSocket != null) && !serverSocket->isClosed()) {
                        JSocket* socket = serverSocket->accept();
                        JConnectionHeaderReader* connectionHeaderReader = new JConnectionHeaderReader(socket, this);
                        connectionReaders->add(connectionHeaderReader);
                        executorService->submit(connectionHeaderReader);
                    }
                }

                void JTransport::stopExport(){
                    serverSocket->close();
                    future->cancel();
                    synchronized(this,{
                        JPrimitiveObjectArray* arr=connectionReaders->toArray();
                        for (jint i=0;i<arr->size();i++){
                            JConnectionHeaderReader* reader=dynamic_cast<JConnectionHeaderReader*>(arr->get(i));
                            reader->unexport();
                        }
                        arr=remoteConnectionsMap->values()->toArray();
                        for (jint i=0;i<arr->size();i++){
                            JConnections* conns=dynamic_cast<JConnections*>(arr->get(i));
                            conns->killAll();
                        }
                        remoteConnectionsMap->clear();
                        connectionReaders->clear();
                    })
                }

                void JTransport::remove(JConnectionHeaderReader* reader){
                    synchronized(this,{
                        connectionReaders->remove(reader);
                    })
                }

                void JTransport::remove(JConnections* connections){
                    synchronized(this,{
                        remoteConnectionsMap->remove(connections->getRemoteEndPoint());
                    })
                }

                JTransport::~JTransport(){
                }
            }
        }
    }
}


