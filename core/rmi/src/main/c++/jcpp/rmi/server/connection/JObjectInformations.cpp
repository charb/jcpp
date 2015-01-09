#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/rmi/server/connection/JObjectInformation.h"
#include "jcpp/rmi/server/connection/JGCClient.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{


                JObjectInformations::JObjectInformations(JILifecycle* lifecycle, JServer* server, JGC* gc, JGCClient* gcClient,JIInvocationListener* invListener) : JObject(getClazz()){
                    this->idMap = new JHashMap();
                    this->objectMap = new JHashMap();
                    this->lifecycle = lifecycle;
                    this->server = server;
                    this->gc = gc;
                    this->gcClient = gcClient;
                    this->invocationListener=invListener;
                    this->methodDigester = new JMethodDigester();
                }

                void JObjectInformations::setTransport(JTransport* transport){
                    this->transport=transport;
                }

                JTransport* JObjectInformations::getTransport(){
                    return transport;
                }

                JServer* JObjectInformations::getServer(){
                    return server;
                }

                JGC* JObjectInformations::getGC(){
                    return gc;
                }

                JGCClient* JObjectInformations::getGCClient(){
                    return gcClient;
                }

                JIInvocationListener* JObjectInformations::getInvocationListener(){
                    return this->invocationListener;
                }

                JMethodDigester* JObjectInformations::getMethodDigester(){
                    return methodDigester;
                }

                void JObjectInformations::doExport(JString* id, JObject* object, JList* interfaces){
                    JObjectInformation* objInfo=null;
                    synchronized(this,{
                        objInfo=dynamic_cast<JObjectInformation*>(idMap->get(id));
                        if (objInfo != null) {
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append("Object[")
                                   ->append(object)
                                   ->append("] with ID[")
                                   ->append(id)
                                   ->append("] already exists in ObjectInformations idMap");
                            throw new JConnectionException(builder->toString());
                        }
                        objInfo=dynamic_cast<JObjectInformation*>(objectMap->get(object));
                        if ( objInfo!= null) {
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append("Object[")
                                   ->append(object)
                                   ->append("] with ID[")
                                   ->append(id)
                                   ->append("] already exists in ObjectInformations objectMap");
                            throw new JConnectionException(builder->toString());
                        }
                        objInfo = new JObjectInformation(id, object, interfaces, this, lifecycle, gc);
                        idMap->put(id, objInfo);
                        objectMap->put(object, objInfo);
                        if (idMap->size() == 1) {
                            transport->startExport();
                        }
                    })
                    objInfo->exported();
                }

                JObjectInformation* JObjectInformations::unexport(JString* id){
                    JObjectInformation* objInfo = remove(id);
                    if (objInfo != null) {
                        objInfo->unexport();
                    }
                    return objInfo;
                }

                JObjectInformation* JObjectInformations::unexport(JObject* object){
                    JObjectInformation* objInfo=null;
                    synchronized(this,{
                        objInfo=dynamic_cast<JObjectInformation*>(objectMap->get(object));
                    })
                    if (objInfo != null) {
                        return unexport(objInfo->getId());
                    }
                    return null;
                }

                void JObjectInformations::unexport(){
                    JMap* objInfoArray=null;
                    synchronized(this,{
                        objInfoArray=new JHashMap(objectMap);
                        objectMap->clear();
                        idMap->clear();
                    })
                    JIterator* it=objInfoArray->values()->iterator();
                    while (it->hasNext()){
                        JObjectInformation* oi=dynamic_cast<JObjectInformation*>(it->next());
                        oi->unexport();
                    }
                    transport->stopExport();
                    methodDigester->clear();
                }

                JPrimitiveObjectArray* JObjectInformations::list(){
                    synchronized(this,{
                        JPrimitiveObjectArray* ar=new JPrimitiveObjectArray(JString::getClazz(),idMap->size());
                        return idMap->keySet()->toArray(ar);
                    })
                }

                JObjectInformation* JObjectInformations::getObjectInformation(JString* id){
                    synchronized(this,{
                        return dynamic_cast<JObjectInformation*>(idMap->get(id));
                    })
                }

                JObjectInformation* JObjectInformations::getObjectInformation(JObject* object){
                    synchronized(this,{
                        return dynamic_cast<JObjectInformation*>(objectMap->get(object));
                    })
                }

                JObjectInformation* JObjectInformations::remove(JString* id){
                    synchronized(this,{
                        JObjectInformation* objInfo=dynamic_cast<JObjectInformation*>(idMap->get(id));
                        if (objInfo != null) {
                            idMap->remove(id);
                            objectMap->remove(objInfo->getObject());
                            if (idMap->size() == 0) {
                                transport->stopExport();
                            }
                        }
                        return objInfo;
                    })
                }

                JObjectInformations::~JObjectInformations(){
                }
            }
        }
    }
}



