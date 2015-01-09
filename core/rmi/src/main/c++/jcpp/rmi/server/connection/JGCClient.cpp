#include "jcpp/rmi/server/connection/JGCClient.h"
#include "jcpp/util/JHashMap.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JGCClient::JGCClient(JServer* localServer, JIGCClientListener* gcClientListener):JObject(getClazz()){
                    this->localServer=localServer;
                    this->endPointInfos=new JHashMap();
                    this->gcClientListener=gcClientListener;
                }

                JPrimitiveObjectArray* JGCClient::getEndPoints(){
                    synchronized(this,{
                        JPrimitiveObjectArray* ar=new JPrimitiveObjectArray(JEndPoint::getClazz(),endPointInfos->size());
                        return endPointInfos->keySet()->toArray(ar);
                    })
                }

                void JGCClient::add(JMap* objectPointers){
                    synchronized(this,{
                        JIterator* it=objectPointers->entrySet()->iterator();
                        while (it->hasNext()){
                            JMap::JEntry* entry=dynamic_cast<JMap::JEntry*>(it->next());
                            JObjectPointer* remoteOP = dynamic_cast<JObjectPointer*>(entry->getKey());
                            JEndPoint* remoteEndPoint = remoteOP->getEndPoint();
                            JGCClientEndPointInfo* endPointInfo = dynamic_cast<JGCClientEndPointInfo*>(endPointInfos->get(remoteEndPoint));
                            if (endPointInfo == null) {
                                endPointInfo = new JGCClientEndPointInfo(this,localServer,remoteEndPoint);
                                endPointInfos->put(remoteEndPoint, endPointInfo);
                            }
                            endPointInfo->doExport(remoteOP->getId(), entry->getValue());
                        }
                    })
                }

                void JGCClient::remove(JEndPoint* endPoint){
                    synchronized(this,{
                        endPointInfos->remove(endPoint);
                    })
                }

                void JGCClient::unexport(){
                    JPrimitiveObjectArray* epis=null;
                    synchronized(this,{
                        epis=endPointInfos->values()->toArray();
                    })
                    for (jint i=0;i<epis->size();i++){
                        JGCClientEndPointInfo* epi=dynamic_cast<JGCClientEndPointInfo*>(epis->get(i));
                        epi->unexport();
                    }
                }

                JIGCClientListener* JGCClient::getGCClientListener(){
                    return gcClientListener;
                }

                JGCClient::~JGCClient(){
                }
            }
        }
    }
}


