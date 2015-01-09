#include "jcpp/rmi/server/connection/JGCEndPointInfo.h"
#include "jcpp/util/JHashMap.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JGCEndPointInfo::JGCEndPointInfo(JGC* gc,JEndPoint* remoteEndPoint):JObject(getClazz()) {
                    this->lastPingId=0;
                    this->previousPingId=-1;
                    this->scheduledFuture=null;
                    this->gc=gc;
                    this->exportedObjects = new JHashMap();
                    this->remoteEndPoint = remoteEndPoint;
                    this->bIsRunning = false;
                }

                jbool JGCEndPointInfo::isUpdated(){
                    synchronized(this,{
                        return previousPingId != lastPingId;
                    })
                }

                JEndPoint* JGCEndPointInfo::getRemoteEndPoint(){
                    return remoteEndPoint;
                }

                void JGCEndPointInfo::doExport(JObjectInformation* objInfo){
                    synchronized(this,{
                        if (exportedObjects->size() == 0) {
                            scheduledFuture = gc->getScheduledExecutorService()->scheduleAtFixedRate(this, gc->getConnectionConfiguration()->getGcTimeout()->get(), gc->getConnectionConfiguration()->getGcTimeout()->get());
                        }
                        if (exportedObjects->get(objInfo->getId()) == null) {
                            exportedObjects->put(objInfo->getId(), objInfo);
                            objInfo->doExport(this);
                        }
                    })
                }

                void JGCEndPointInfo::unexport(JObjectInformation* objInfo){
                    JObjectInformation* removedObjInfo=null;
                    jint size=0;
                    synchronized(this,{
                        removedObjInfo=dynamic_cast<JObjectInformation*>(exportedObjects->get(objInfo->getId()));
                        exportedObjects->remove(objInfo->getId());
                        size = exportedObjects->size();
                    })
                    if (removedObjInfo != null) {
                        if (size == 0) {
                            unexport();
                        }
                    }
                }

                void JGCEndPointInfo::unexport(){
                    JPrimitiveObjectArray* objInfos=null;
                    synchronized(this,{
                        objInfos=exportedObjects->values()->toArray();
                        gc->remove(remoteEndPoint);
                        if (scheduledFuture!=null){
                            scheduledFuture->cancel();
                        }
                        scheduledFuture = null;
                    })
                    for (jint i=0;i<objInfos->size();i++){
                        JObjectInformation* objInfo= dynamic_cast<JObjectInformation*>(objInfos->get(i));
                        objInfo->unexport(remoteEndPoint);
                    }
                }

                void JGCEndPointInfo::update(){
                    synchronized(this,{
                        previousPingId = lastPingId;
                    })
                }

                void JGCEndPointInfo::ping(JPrimitiveBooleanArray* returnPing, JPrimitiveObjectArray* ids){
                    synchronized(this,{
                        lastPingId = lastPingId + 1;
                        for (jint i = 0; i < ids->size(); i++) {
                            if (exportedObjects->get(ids->get(i))!=null) {
                                returnPing->setBoolean(i,true);
                            }else{
                                returnPing->setBoolean(i,false);
                            }
                        }
                    })
                }

                jbool JGCEndPointInfo::isRunning(){
                    synchronized(this,{
                        return this->bIsRunning;
                    })
                }

                void JGCEndPointInfo::setRunning(jbool b){
                    synchronized(this,{
                        this->bIsRunning=b;
                    })
                }

                void JGCEndPointInfo::run(){
                    if (!isRunning()) {
                        setRunning(true);
                        if (isUpdated()) {
                            update();
                        } else {
                            unexport();
                        }
                        setRunning(false);
                    }
                }

                JGCEndPointInfo::~JGCEndPointInfo(){
                }
            }
        }
    }
}


