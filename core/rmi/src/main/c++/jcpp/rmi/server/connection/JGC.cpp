#include "jcpp/rmi/server/connection/JGC.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JGC::JGC(JExecutorService* executorService, JScheduledExecutorService* scheduledExecutorService, JConnectionConfiguration* connectionConfiguration):JObject(getClazz()){
                    this->endPointInfos = new JHashMap();
                    this->executorService = executorService;
                    this->scheduledExecutorService = scheduledExecutorService;
                    this->connectionConfiguration = connectionConfiguration;
                }

                JPrimitiveObjectArray* JGC::getExportedEndPoints(){
                    synchronized(this,{
                        JPrimitiveObjectArray* ar=new JPrimitiveObjectArray(JEndPoint::getClazz(),endPointInfos->size());
                        ar=endPointInfos->keySet()->toArray(ar);
                        return ar;
                    })
                }

                JScheduledExecutorService* JGC::getScheduledExecutorService(){
                    return scheduledExecutorService;
                }

                JConnectionConfiguration* JGC::getConnectionConfiguration(){
                    return connectionConfiguration;
                }

                JPrimitiveBooleanArray* JGC::ping(JEndPoint* endPoint, JPrimitiveObjectArray* ids){
                    JPrimitiveBooleanArray* returnPing=new JPrimitiveBooleanArray(ids->size());
                    synchronized(this,{
                        JGCEndPointInfo* endPointInfo = dynamic_cast<JGCEndPointInfo*>(endPointInfos->get(endPoint));
                        if (endPointInfo != null) {
                            endPointInfo->ping(returnPing, ids);
                        }
                        return returnPing;
                    })
                }

                void JGC::doExport(JList* objInfoSet, JEndPoint* endPoint){
                    synchronized(this,{
                        for (jint i=0;i<objInfoSet->size();i++){
                            JObjectInformation* objInfo=dynamic_cast<JObjectInformation*>(objInfoSet->get(i));
                            doExport(objInfo, endPoint);
                        }
                    })
                }

                void JGC::unexport(JEndPoint* endPoint){
                    JGCEndPointInfo* endPointInfo=null;
                    synchronized(this,{
                        endPointInfo= dynamic_cast<JGCEndPointInfo*>(endPointInfos->get(endPoint));
                    })
                    if (endPointInfo != null) {
                        endPointInfo->unexport();
                    }
                }

                void JGC::unexport(){
                    JMap* infos=null;
                    synchronized(this,{
                        infos = new JHashMap(endPointInfos);
                    })
                    JIterator* it=infos->values()->iterator();
                    while (it->hasNext()){
                        JGCEndPointInfo* epi=dynamic_cast<JGCEndPointInfo*>(it->next());
                        epi->unexport();
                    }
                }

                void JGC::endPointDead(JEndPoint* endPoint){
                    unexport(endPoint);
                }

                void JGC::doExport(JObjectInformation* objInfo, JEndPoint* endPoint){
                    JGCEndPointInfo* endPointInfo=null;
                    synchronized(this,{
                        endPointInfo = dynamic_cast<JGCEndPointInfo*>(endPointInfos->get(endPoint));
                        if (endPointInfo == null) {
                            endPointInfo = new JGCEndPointInfo(this,endPoint);
                            endPointInfos->put(endPoint, endPointInfo);
                        }
                    })
                    endPointInfo->doExport(objInfo);
                }

                void JGC::remove(JEndPoint* e){
                    synchronized(this,{
                        endPointInfos->remove(e);
                    })
                }

                JGC::~JGC(){
                }
            }
        }
    }
}

