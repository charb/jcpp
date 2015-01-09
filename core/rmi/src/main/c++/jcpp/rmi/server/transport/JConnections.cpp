#include "jcpp/rmi/server/transport/JConnections.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/rmi/server/transport/JConnection.h"
#include "jcpp/rmi/server/transport/JSocketConnection.h"
#include "jcpp/rmi/server/transport/JTransport.h"
#include "jcpp/util/JArrayList.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{


                JConnections::JConnections(JEndPoint* remoteEndPoint, JTransport* transport):JObject(getClazz()) {
                    this->remoteEndPoint=remoteEndPoint;
                    this->transport=transport;
                    this->freeConnectionList=new JArrayList();
                    this->takenConnectionList=new JArrayList();
                    this->connectionTimeout=transport->getTransportConfiguration()->getConnectionPoolTimeout()->get();
                    launchTimeoutTimer();
                }

                JConnection* JConnections::createConnection(){
                    synchronized(this,{
                        JConnection* connection=null;
                        jint socketTimeout = transport->getTransportConfiguration()->getSocketTimeout()->get();
                        while (freeConnectionList->size() > 0) {
                            connection = dynamic_cast<JConnection*>(freeConnectionList->remove(0));
                            if (!connection->isDead()) {
                                takenConnectionList->add(connection);
                                connection->setSoTimeout(socketTimeout);
                                break;
                            }else{
                                connection->kill();
                            }
                        }
                        if (connection==null){
                            JRoute* route = transport->getTransportRouter()->findRoute(transport->getLocalEndPoint()->getSite(), remoteEndPoint);
                            if ((route == null) || (route->getAddressList()->size() == 0)) {
                                JStringBuilder* builder=new JStringBuilder();
                                builder->append("No route found from [")
                                       ->append(transport->getLocalEndPoint()->toString())
                                       ->append("] to [")
                                       ->append(remoteEndPoint->toString())
                                       ->append("]");
                                throw new JIOException(builder->toString());
                            }
                            connection = new JSocketConnection(route, this, transport->getTransportConfiguration()->getGatewayConfiguration());
                            takenConnectionList->add(connection);
                            connection->setSoTimeout(socketTimeout);
                        }
                        return connection;
                    })
                }

                jlong JConnections::getConnectionTimeout(){
                    return connectionTimeout;
                }

                void JConnections::freeAll(){
                    synchronized(this,{
                        for (jint i=0;i<takenConnectionList->size();i++){
                            JConnection* conn=dynamic_cast<JConnection*>(takenConnectionList->get(i));
                            conn->free();
                        }
                    })
                }

                void JConnections::killAll(){
                    synchronized(this,{
                        for (jint i=0;i<takenConnectionList->size();i++){
                            JConnection* conn=dynamic_cast<JConnection*>(takenConnectionList->get(i));
                            conn->kill();
                        }
                        for (jint i=0;i<freeConnectionList->size();i++){
                            JConnection* conn=dynamic_cast<JConnection*>(freeConnectionList->get(i));
                            conn->kill();
                        }
                        takenConnectionList->clear();
                        freeConnectionList->clear();
                        remove();
                    })
                }

                JEndPoint* JConnections::getRemoteEndPoint(){
                    return remoteEndPoint;
                }

                JTransport* JConnections::getTransport(){
                    return transport;
                }

                void JConnections::free(JConnection* connection){
                    synchronized(this,{
                        if (takenConnectionList->remove(connection)){
                            connection->setLastUsed();
                            freeConnectionList->add(0,connection);
                        }
                    })
                }

                void JConnections::kill(JConnection* connection){
                    synchronized(this,{
                        takenConnectionList->remove(connection);
                        freeConnectionList->remove(connection);
                        if (takenConnectionList->size()==0 && freeConnectionList->size()==0){
                            remove();
                        }
                    })
                }

                void JConnections::remove(){
                    scheduledFuture->cancel();
                    transport->remove(this);
                }

                void JConnections::run(){
                    JString* oldName = JThread::currentThread()->getName();
                    JThrowable* thrown=null;
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Connections Timeout Thread - ")
                           ->append(toString());
                    JThread::currentThread()->setName(builder->toString());

                    try {
                        JList* freeArray=null;
                        synchronized(this,{
                            freeArray=new JArrayList(freeConnectionList);
                        })
                        jlong currentTime=JSystem::currentTimeMillis();
                        for (jint i=0;i<freeArray->size();i++){
                            JConnection* conn=dynamic_cast<JConnection*>(freeArray->get(i));
                            jlong diff = currentTime - conn->getLastUsed();
                            if (diff > getConnectionTimeout()) {
                                try {
                                    conn->kill();
                                } catch (JThrowable* ex) {//TODO log
                                    ex->printStackTrace();
                                }
                            }
                        }
                    }catch(JThrowable* t){
                        thrown=t;
                    }
                    JThread::currentThread()->setName(oldName);

                    if (thrown!=null){
                        throw thrown;
                    }
                }

                void JConnections::launchTimeoutTimer(){
                    scheduledFuture=transport->getScheduledExecutorService()->scheduleAtFixedRate(this,transport->getTransportConfiguration()->getTimeoutTimerInterval()->get(), transport->getTransportConfiguration()->getTimeoutTimerInterval()->get());
                }

                JString* JConnections::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Connections[localEndPoint=")
                           ->append(transport->getLocalEndPoint())
                           ->append(", removeEndPoint=")
                           ->append(remoteEndPoint)
                           ->append("]");
                    return builder->toString();
                }

                JConnections::~JConnections(){
                }
            }
        }
    }
}


