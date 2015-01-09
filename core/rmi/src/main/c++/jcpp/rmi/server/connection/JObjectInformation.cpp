#include "jcpp/rmi/server/connection/JObjectInformation.h"
#include "jcpp/rmi/server/connection/JObjectHandler.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{


                JObjectInformation::JObjectInformation(JString* id, JObject* object, JList* interfaces, JObjectInformations* objectInformations, JILifecycle* lifecycle, JGC*) : JObject(getClazz()){
                    this->object = object;
                    this->id = id;
                    this->objectInformations = objectInformations;
                    this->objectHandler = new JObjectHandler(objectInformations, object->getClass()->getClassLoader(), interfaces, new JObjectPointer(objectInformations->getTransport()->getLocalEndPoint(), id));
                    this->lifecycle = lifecycle;
                    this->exportedEndPoints = new JHashMap();
                }

                JObject* JObjectInformation::getObject(){
                    return object;
                }

                JString* JObjectInformation::getId(){
                    return id;
                }

                JILifecycle* JObjectInformation::getLifecycle(){
                    return lifecycle;
                }

                JObjectHandler* JObjectInformation::getObjectHandler(){
                    return objectHandler;
                }

                void JObjectInformation::exported(){
                    lifecycle->doExport(this);
                }

                void JObjectInformation::doExport(JGCEndPointInfo* remoteEndPointInfo){
                    synchronized(this,{
                        exportedEndPoints->put(remoteEndPointInfo->getRemoteEndPoint(),remoteEndPointInfo);
                    })
                    lifecycle->doExport(this,remoteEndPointInfo->getRemoteEndPoint());
                }

                void JObjectInformation::unexport(JEndPoint* endPoint){
                    synchronized(this,{
                        exportedEndPoints->remove(endPoint);
                    })
                    lifecycle->unexport(this,endPoint);
                }

                void JObjectInformation::unexport(){
                    objectInformations->remove(id);
                    JMap* endPointInfos=null;
                    synchronized(this,{
                        endPointInfos=new JHashMap(exportedEndPoints);
                        exportedEndPoints->clear();
                    })
                    JIterator* it=endPointInfos->entrySet()->iterator();
                    while (it->hasNext()){
                        JMap::JEntry* entry=dynamic_cast<JMap::JEntry*>(it->next());
                        JGCEndPointInfo* ei=dynamic_cast<JGCEndPointInfo*>(entry->getValue());
                        ei->unexport(this);
                        lifecycle->unexport(this,ei->getRemoteEndPoint());
                    }
                    lifecycle->unexport(this);
                }

                JString* JObjectInformation::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("ObjectInformation[Id[")
                           ->append(id)
                           ->append("], Object[")
                           ->append(object)
                           ->append("]]");
                    return builder->toString();
                }

                JObjectInformation::~JObjectInformation(){
                }
            }
        }
    }
}


