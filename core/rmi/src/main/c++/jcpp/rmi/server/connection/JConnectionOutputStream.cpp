#include "jcpp/rmi/server/connection/JConnectionOutputStream.h"
#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/rmi/server/connection/JObjectHandler.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/rmi/server/connection/serialization/JINotSerializableObjectHandler.h"
#include "jcpp/rmi/server/connection/JINotExportedObjectListener.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::rmi::server::connection::serialization;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JConnectionOutputStream::JConnectionOutputStream(JOutputStream* out, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint):JObjectOutputStream(out,getClazz()){
                    this->enableReplaceObject(true);
                    this->objectInformations = objectInformations;
                    this->remoteEndPoint = remoteEndPoint;
                    this->exportedObjInfos = new JArrayList();
                }

                void JConnectionOutputStream::done(){
                    objectInformations->getGC()->doExport(exportedObjInfos, remoteEndPoint);
                    exportedObjInfos->clear();
                }

                JObject* JConnectionOutputStream::replaceObject(JObject* obj){
                    JObjectInformation* objInfo = objectInformations->getObjectInformation(obj);
                    if ((objInfo == null) && (obj != null) && !(JSerializable::getClazz()->isAssignableFrom(obj->getClass()))) {
                        jbool isExported = false;
                        JINotExportedObjectListener* notExportedObjectListener = objectInformations->getServer()->getNotExportedObjectListener();
                        if (notExportedObjectListener != null) {
                            isExported = notExportedObjectListener->handleNotExportedObject(obj);
                            if (isExported) {
                                objInfo = objectInformations->getObjectInformation(obj);
                            }
                        }
                        JINotSerializableObjectHandler* notSerializableObjectHandler = objectInformations->getServer()->getNotSerializableObjectHandler();
                        if (!isExported && (notSerializableObjectHandler != null)) {
                            return notSerializableObjectHandler->handleNotSerializableObject(obj);
                        }
                    }
                    if (objInfo != null) {
                        exportedObjInfos->add(objInfo);
                        JObjectHandler* objectHandler = (JObjectHandler*) objInfo->getObjectHandler()->clone();
                        return objectHandler->getProxy();
                    }
                    return obj;
                }

                JConnectionOutputStream::~JConnectionOutputStream(){
                }
            }
        }
    }
}



