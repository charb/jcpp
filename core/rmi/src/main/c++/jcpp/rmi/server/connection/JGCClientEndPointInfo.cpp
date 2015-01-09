#include "jcpp/rmi/server/connection/JGCClientEndPointInfo.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JGCClientEndPointInfo::JGCClientEndPointInfo(JGCClient* gcClient,JServer* localServer,JEndPoint* remoteEndPoint) : JObject(getClazz()){
                    this->scheduledFuture=null;
                    this->gcExceptionCount=0;
                    this->bIsRunning = false;
                    this->throwable=null;
                    this->gcClient=gcClient;
                    this->localServer=localServer;
                    this->remoteEndPoint = remoteEndPoint;
                    this->objects = new JHashMap();
                    this->gc = dynamic_cast<JIGC*>(localServer->lookup(remoteEndPoint, JIGC::getClazz()));
                    this->connections = localServer->getObjectInformations()->getTransport()->getConnections(remoteEndPoint);
                }

                void JGCClientEndPointInfo::doExport(JString* id, JObject* object){
                    synchronized(this,{
                        if (objects->size() == 0) {
                            scheduledFuture = localServer->getScheduledExecutorService()->scheduleAtFixedRate(this, localServer->getConnectionConfiguration()->getGcClientTimeout()->get(),localServer->getConnectionConfiguration()->getGcClientTimeout()->get());
                        }
                        objects->put(id, object);
                    })
                }

                void JGCClientEndPointInfo::unexport(JString* id){
                    synchronized(this,{
                        objects->remove(id);
                        if (objects->size() == 0) {
                            unexport();
                        }
                    })
                }

                jbool JGCClientEndPointInfo::ping(){
                    jbool bresult=true;
                    throwable = null;
                    JPrimitiveObjectArray* idsArray=null;
                    synchronized(this,{
                        idsArray = new JPrimitiveObjectArray(JString::getClazz(),objects->size());
                        idsArray=objects->keySet()->toArray(idsArray);
                    })
                    JPrimitiveBooleanArray* ping = null;
                    try {
                        ping = gc->ping(localServer->getEndPoint(), idsArray);
                    } catch (JThrowable* e) {
                        e->printStackTrace();//TODO cout
                        throwable = e;
                        if (++gcExceptionCount >= localServer->getConnectionConfiguration()->getGcClientExceptionThreshold()->get()) {
                            unexport();
                            bresult=false;
                        }
                        bresult=true;
                    }
                    if (ping!=null){
                        gcExceptionCount = 0;
                        for (jint i = 0; i < ping->size(); i++) {
                            jbool b=ping->getBoolean(i);
                            if (!b) {
                                unexport(dynamic_cast<JString*>(idsArray->get(i)));
                            }
                        }
                        synchronized(this,{
                            if (objects->size() == 0) {
                                bresult=false;
                            }
                        })
                    }
                    return bresult;
                }

                void JGCClientEndPointInfo::unexport(){
                    synchronized(this,{
                        gcClient->remove(remoteEndPoint);
                        if (scheduledFuture!=null){
                            scheduledFuture->cancel();
                        }
                        scheduledFuture=null;
                    })
                }

                jbool JGCClientEndPointInfo::isRunning(){
                    synchronized(this,{
                        return this->bIsRunning;
                    })
                }

                void JGCClientEndPointInfo::setRunning(bool b){
                    synchronized(this,{
                        this->bIsRunning=b;
                    })
                }

                JPrimitiveObjectArray* JGCClientEndPointInfo::getObjects(){
                    synchronized(this,{
                        return objects->values()->toArray();
                    })
                }

                void JGCClientEndPointInfo::run(){
                    if (!isRunning()) {
                        setRunning(true);
                        jbool bping = ping();
                        JPrimitiveObjectArray* values=getObjects();
                        if (!bping) {
                            if (gcExceptionCount == 0) {
                                gcClient->getGCClientListener()->objectDead(remoteEndPoint, values);
                            } else {
                                gcClient->getGCClientListener()->objectDead(remoteEndPoint, values,throwable);
                            }
                        } else {
                            if (gcExceptionCount == 0) {
                                gcClient->getGCClientListener()->objectAlive(remoteEndPoint, values);
                            } else {
                                gcClient->getGCClientListener()->objectMaybeDead(remoteEndPoint, values, throwable);
                            }
                        }
                        setRunning(false);
                    }
                }

                JGCClientEndPointInfo::~JGCClientEndPointInfo(){
                }
            }
        }
    }
}



