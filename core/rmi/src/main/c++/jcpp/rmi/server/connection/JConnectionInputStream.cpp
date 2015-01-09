#include "jcpp/rmi/server/connection/JConnectionInputStream.h"
#include "jcpp/rmi/server/connection/JObjectHandler.h"
#include "jcpp/rmi/server/connection/JGCClient.h"
#include "jcpp/rmi/server/connection/JInvoker.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/io/JNotSerializableException.h"
#include "jcpp/util/JHashMap.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JConnectionInputStream::JConnectionInputStream(JInputStream* in, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint):JObjectInputStream(in,getClazz()){
                    this->enableResolveObject(true);
                    this->objectInformations = objectInformations;
                    this->gcObjectPointers = new JHashMap();
                    this->remoteEndPoint = remoteEndPoint;
                }

                void JConnectionInputStream::done(){
                    objectInformations->getGCClient()->add(gcObjectPointers);
                    gcObjectPointers->clear();
                }

                JObject* JConnectionInputStream::resolveObject(JObject* obj){
                    if (obj->getClass()->isProxy()) {
                        JInvocationHandler* invocationHandler = (dynamic_cast<JProxy*>(obj))->getInvocationHandler();
                        JObject* oih=dynamic_cast<JObject*>(invocationHandler);
                        if (oih->getClass()==JObjectHandler::getClazz()) {
                            JObjectHandler* objectHandler = dynamic_cast<JObjectHandler*>(invocationHandler);
                            objectHandler->setObjectInformations(objectInformations);
                            JObjectPointer* objectPointer = objectHandler->getInvoker()->getObjectPointer();
                            if (objectPointer->getEndPoint()->equals(objectInformations->getTransport()->getLocalEndPoint())) {
                                return objectInformations->getObjectInformation(objectPointer->getId())->getObject();
                            }
                            gcObjectPointers->put(objectPointer, obj);
                            return obj;
                        }

                    } else if (obj->getClass()==JNotSerializableException::getClazz()) {
                        throw dynamic_cast<JNotSerializableException*>(obj);
                    }
                    return obj;
                }

                JConnectionInputStream::~JConnectionInputStream(){
                }
            }
        }
    }
}


