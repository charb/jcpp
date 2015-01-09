#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/util/concurrent/JThreadPoolExecutor.h"
#include "jcpp/util/concurrent/JSynchronousQueue.h"
#include "jcpp/util/concurrent/JExecutors.h"
#include "jcpp/util/concurrent/JScheduledThreadPoolExecutor.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/rmi/server/connection/JInvoker.h"

using namespace jcpp::util::concurrent;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{


                JServer::JServer(JEndPoint* endPoint, JITransportRouter* transportRouter, JConnectionConfiguration* connectionConfiguration): JObject(getClazz()){
                    this->notExportedObjectListener=null;
                    this->notSerializableObjectHandler=null;
                    this->invocationExceptionHandler=null;
                    this->endPoint = endPoint;
                    this->connectionConfiguration = connectionConfiguration;
                    this->lifecycles = new JArrayList();
                    this->gcClientListeners = new JArrayList();
                    this->invocationListeners=new JArrayList();
                    this->executorService = new JThreadPoolExecutor(0, JInteger::MAX_VALUE, 30L,new JSynchronousQueue());
                    this->scheduledExecutorService = JExecutors::newScheduledThreadPool(connectionConfiguration->getExecutorCorePoolSize()->get());
                    this->gc = new JGC(executorService, scheduledExecutorService, connectionConfiguration);
                    this->gcClient = new JGCClient(this, this);
                    this->objectInformations = new JObjectInformations(this, this, gc, gcClient,this);
                    this->connectionTransportDispatcher = new JConnectionTransportDispatcher(objectInformations);
                    this->transport = new JTransport(endPoint, transportRouter, connectionTransportDispatcher, executorService, scheduledExecutorService, connectionConfiguration->getTransportConfiguration());
                    this->objectInformations->setTransport(transport);
                    this->registry = new JRegistry(objectInformations);
                    this->iregistry = registry;

                    JList* inter=new JArrayList();
                    inter->add(JIRegistry::getClazz());
                    this->registry->bind(JIRegistry::getClazz()->getName(), registry, inter);
                    
                    inter=new JArrayList();
                    inter->add(JIServer::getClazz());
                    this->registry->bind(JIServer::getClazz()->getName(), this, inter);
                    
                    inter=new JArrayList();
                    inter->add(JIGC::getClazz());
                    this->registry->bind(JIGC::getClazz()->getName(), gc, inter);

                    inter=new JArrayList();
                    inter->add(JIGCClient::getClazz());
                    this->registry->bind(JIGCClient::getClazz()->getName(), gcClient, inter);
                }

                JIServer* JServer::getRemoteServer(JObject* object){
                    if (object->getClass()->isProxy()){
                        JObjectHandler* objectHandler = getObjectHandlerFromProxy(object);
                        JObjectPointer* objectPointer = objectHandler->getInvoker()->getObjectPointer();
                        return dynamic_cast<JIServer*>(objectHandler->getInvoker()->getObjectInformations()->getServer()->lookup(objectPointer->getEndPoint(), JIServer::getClazz()));
                    }
                    return null;
                }

                JIServer* JServer::getLocalServer(JObject* object){
                    JObjectHandler* objectHandler = getObjectHandlerFromProxy(object);
                    return objectHandler->getInvoker()->getObjectInformations()->getServer();
                }

                JString* JServer::getHost(JObject* object){
                    return getEndPoint(object)->getAddress()->getHostName();
                }

                jint JServer::getPort(JObject* object){
                    return getEndPoint(object)->getAddress()->getPort();
                }

                JString* JServer::getSite(JObject* object){
                    return getEndPoint(object)->getSite();
                }

                JEndPoint* JServer::getEndPoint(JObject* object){
                    if (object->getClass()->isProxy()) {
                        JObjectPointer* objectPointer = getObjectHandlerFromProxy(object)->getInvoker()->getObjectPointer();
                        return objectPointer->getEndPoint();
                    }
                    return null;
                }

                JString* JServer::getId(JObject* object){
                    if (object->getClass()->isProxy()) {
                        JObjectPointer* objectPointer = getObjectHandlerFromProxy(object)->getInvoker()->getObjectPointer();
                        return objectPointer->getId();
                    }
                    return null;
                }

                JObject* JServer::lookup(JEndPoint* endPoint, JClass* clazz){
                    JList* inter=new JArrayList();
                    inter->add(clazz);
                    JObjectHandler* objectHandler = new JObjectHandler(objectInformations, clazz->getClassLoader(), inter, new JObjectPointer(endPoint, clazz->getName()));
                    return objectHandler->getProxy();
                }

                JObject* JServer::lookup(JString* id, JEndPoint* endPoint, JClassLoader* classLoader, JList* interfaces){
                    JObjectHandler* objectHandler = new JObjectHandler(objectInformations, classLoader, interfaces, new JObjectPointer(endPoint, id));
                    return objectHandler->getProxy();
                }

                JIRegistry* JServer::getIRegistry(){
                    return iregistry;
                }

                JEndPoint* JServer::getEndPoint(){
                    return endPoint;
                }

                JIGC* JServer::getGC(){
                    return gc;
                }

                JIGCClient* JServer::getGCClient(){
                    return gcClient;
                }

                JExecutorService* JServer::getExecutorService(){
                    return executorService;
                }

                JScheduledExecutorService* JServer::getScheduledExecutorService(){
                    return scheduledExecutorService;
                }

                JObjectInformations* JServer::getObjectInformations(){
                    return objectInformations;
                }

                JConnectionTransportDispatcher* JServer::getConnectionTransportDispatcher(){
                    return connectionTransportDispatcher;
                }

                JConnectionConfiguration* JServer::getConnectionConfiguration(){
                    return connectionConfiguration;
                }

                JINotExportedObjectListener* JServer::getNotExportedObjectListener(){
                    return notExportedObjectListener;
                }

                void JServer::setNotExportedObjectListener(JINotExportedObjectListener* notExportedObjectListener){
                    this->notExportedObjectListener=notExportedObjectListener;
                }

                JINotSerializableObjectHandler* JServer::getNotSerializableObjectHandler(){
                    return notSerializableObjectHandler;
                }

                void JServer::setNotSerializableObjectHandler(JINotSerializableObjectHandler* notSerializableObjectHandler){
                    this->notSerializableObjectHandler=notSerializableObjectHandler;
                }

                JIInvocationExceptionHandler* JServer::getInvocationExceptionHandler(){
                    return invocationExceptionHandler;
                }

                void JServer::setInvocationExceptionHandler(JIInvocationExceptionHandler* i){
                    this->invocationExceptionHandler=i;
                }

                void JServer::unexport(){
                    gcClient->unexport();
                    gc->unexport();
                    objectInformations->unexport();
                    scheduledExecutorService->shutdown();
                    executorService->shutdown();
                }

                void JServer::addLifecycle(JILifecycle* lifecycle){
                    lifecycles->add(dynamic_cast<JObject*>(lifecycle));
                }

                void JServer::removeLifecycle(JILifecycle* lifecycle){
                    lifecycles->remove(dynamic_cast<JObject*>(lifecycle));
                }

                void JServer::addGCClientListener(JIGCClientListener* gcClientListener){
                    gcClientListeners->add(dynamic_cast<JObject*>(gcClientListener));
                }

                void JServer::removeGCClientListener(JIGCClientListener* gcClientListener){
                    gcClientListeners->remove(dynamic_cast<JObject*>(gcClientListener));
                }

                void JServer::addInvocationListener(JIInvocationListener* i){
                    invocationListeners->add(dynamic_cast<JObject*>(i));
                }

                void JServer::removeInvocationListener(JIInvocationListener* i){
                    invocationListeners->remove(dynamic_cast<JObject*>(i));
                }

                JObjectHandler* JServer::getObjectHandlerFromProxy(JObject* object){
                    if (object->getClass()->isProxy()) {
                        JInvocationHandler* invocationHandler = (dynamic_cast<JProxy*>(object))->getInvocationHandler();
                        if ((dynamic_cast<JObject*>(invocationHandler))->getClass()==JObjectHandler::getClazz()) {
                            JObjectHandler* objectHandler = dynamic_cast<JObjectHandler*>( invocationHandler);
                            return objectHandler;
                        }
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("The Proxy object: ")
                               ->append(object)
                               ->append(" is not an instance of ObjectHandler.");
                        throw new JException(builder->toString());
                    }
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("The object: ")
                           ->append(object)
                           ->append(" is not of type Proxy.");
                    throw new JException(builder->toString());
                }

                void JServer::doExport(JObjectInformation* objectInformation, JEndPoint* endPoint){
                    for (jint i=0;i<lifecycles->size();i++){
                        JILifecycle* l=dynamic_cast<JILifecycle*>(lifecycles->get(i));
                        l->doExport(objectInformation,endPoint);
                    }
                }

                void JServer::unexport(JObjectInformation* objectInformation){
                    for (jint i=0;i<lifecycles->size();i++){
                        JILifecycle* l=dynamic_cast<JILifecycle*>(lifecycles->get(i));
                        l->unexport(objectInformation);
                    }
                }

                void JServer::doExport(JObjectInformation* objectInformation){
                    for (jint i=0;i<lifecycles->size();i++){
                        JILifecycle* l=dynamic_cast<JILifecycle*>(lifecycles->get(i));
                        l->doExport(objectInformation);
                    }
                }

                void JServer::unexport(JObjectInformation* objectInformation, JEndPoint* endPoint){
                    for (jint i=0;i<lifecycles->size();i++){
                        JILifecycle* l=dynamic_cast<JILifecycle*>(lifecycles->get(i));
                        l->unexport(objectInformation,endPoint);
                    }
                }

                void JServer::objectAlive(JEndPoint* endPoint, JPrimitiveObjectArray* objects){
                    for (jint i=0;i<gcClientListeners->size();i++){
                        JIGCClientListener* l=dynamic_cast<JIGCClientListener*>(gcClientListeners->get(i));
                        l->objectAlive(endPoint,objects);
                    }
                }

                void JServer::objectDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects){
                    for (jint i=0;i<gcClientListeners->size();i++){
                        JIGCClientListener* l=dynamic_cast<JIGCClientListener*>(gcClientListeners->get(i));
                        l->objectDead(endPoint,objects);
                    }
                }

                void JServer::objectDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects, JThrowable* throwable){
                    for (jint i=0;i<gcClientListeners->size();i++){
                        JIGCClientListener* l=dynamic_cast<JIGCClientListener*>(gcClientListeners->get(i));
                        l->objectDead(endPoint,objects,throwable);
                    }
                }

                void JServer::objectMaybeDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects, JThrowable* throwable){
                    for (jint i=0;i<gcClientListeners->size();i++){
                        JIGCClientListener* l=dynamic_cast<JIGCClientListener*>(gcClientListeners->get(i));
                        l->objectMaybeDead(endPoint,objects,throwable);
                    }
                }

                void JServer::invocationSucceeded(JObject* proxy, JMethod* method, JList* args){
                    for (jint i=0;i<invocationListeners->size();i++){
                        JIInvocationListener* l=dynamic_cast<JIInvocationListener*>(invocationListeners->get(i));
                        l->invocationSucceeded(proxy,method,args);
                    }
                }

                void JServer::invocationFailed(JObject* proxy, JMethod* method, JList* args, JThrowable* e){
                    for (jint i=0;i<invocationListeners->size();i++){
                        JIInvocationListener* l=dynamic_cast<JIInvocationListener*>(invocationListeners->get(i));
                        l->invocationFailed(proxy,method,args,e);
                    }
                }

                JString* JServer::toString(){
                    return this->endPoint->toString();
                }

                JServer::~JServer(){
                }
            }
        }
    }
}


