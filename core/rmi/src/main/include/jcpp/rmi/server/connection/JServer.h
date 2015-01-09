#ifndef JCPP_RMI_SERVER_CONNECTION_JSERVER_H
#define JCPP_RMI_SERVER_CONNECTION_JSERVER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"
#include "jcpp/rmi/server/connection/JIGCClient.h"
#include "jcpp/rmi/server/connection/JIGC.h"
#include "jcpp/rmi/server/connection/JIServer.h"
#include "jcpp/rmi/server/transport/JTransport.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JINotExportedObjectListener.h"
#include "jcpp/rmi/server/connection/serialization/JINotSerializableObjectHandler.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JObjectHandler.h"
#include "jcpp/rmi/server/connection/JIGCClientListener.h"
#include "jcpp/rmi/server/connection/JGC.h"
#include "jcpp/rmi/server/connection/JGCClient.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectInformation.h"
#include "jcpp/rmi/server/connection/JRegistry.h"
#include "jcpp/rmi/server/connection/JIInvocationExceptionHandler.h"
#include "jcpp/rmi/server/connection/JIInvocationListener.h"
#include "jcpp/rmi/server/connection/JConnectionTransportDispatcher.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JScheduledExecutorService.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::transport;
using namespace jcpp::rmi::server::connection::serialization;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JGC;
                class JGCClient;
                class JConnectionTransportDispatcher;
                // @Class(canonicalName="jcpp.rmi.server.connection.Server", simpleName="Server");
                class JCPP_EXPORT JServer : public JObject, public JIServer, public JILifecycle, public JIGCClientListener, public JIInvocationListener{
                protected:
                    JEndPoint* endPoint;
                    JIRegistry* iregistry;
                    JRegistry* registry;
                    JTransport* transport;
                    JObjectInformations* objectInformations;
                    JList* lifecycles;
                    JList* gcClientListeners;
                    JList* invocationListeners;
                    JINotExportedObjectListener* notExportedObjectListener;
                    JINotSerializableObjectHandler* notSerializableObjectHandler;
                    JGC* gc;
                    JGCClient* gcClient;
                    JScheduledExecutorService* scheduledExecutorService;
                    JExecutorService* executorService;
                    JConnectionTransportDispatcher* connectionTransportDispatcher;
                    JConnectionConfiguration* connectionConfiguration;
                    JIInvocationExceptionHandler*  invocationExceptionHandler;
                    static JObjectHandler* getObjectHandlerFromProxy(JObject* object);


                public:
                    JServer(JEndPoint* endPoint, JITransportRouter* transportRouter, JConnectionConfiguration* connectionConfiguration);

                    static JClass* getClazz();

                    static JIServer* getRemoteServer(JObject* object);
                    
                    static JIServer* getLocalServer(JObject* object);
                    
                    static JString* getHost(JObject* object);
                    
                    static jint getPort(JObject* object);
                    
                    static JString* getSite(JObject* object);
                    
                    static JEndPoint* getEndPoint(JObject* object);
                    
                    static JString* getId(JObject* object);

                    virtual JObject* lookup(JEndPoint* endPoint, JClass* clazz);
                    
                    virtual JObject* lookup(JString* id, JEndPoint* endPoint, JClassLoader* classLoader, JList* interfaces);

                    virtual JIRegistry* getIRegistry();
                    
                    virtual JEndPoint* getEndPoint();
                    
                    virtual JIGC* getGC();
                    
                    virtual JIGCClient* getGCClient();
                    
                    virtual JExecutorService* getExecutorService();
                    
                    virtual JScheduledExecutorService* getScheduledExecutorService();
                    
                    virtual JObjectInformations* getObjectInformations();
                    
                    virtual JConnectionTransportDispatcher* getConnectionTransportDispatcher();
                    
                    virtual JConnectionConfiguration* getConnectionConfiguration();
                    
                    virtual JINotExportedObjectListener* getNotExportedObjectListener();
                    
                    virtual void setNotExportedObjectListener(JINotExportedObjectListener* notExportedObjectListener);
                    
                    virtual JINotSerializableObjectHandler* getNotSerializableObjectHandler();
                    
                    virtual void setNotSerializableObjectHandler(JINotSerializableObjectHandler* notSerializableObjectHandler);
                    
                    virtual JIInvocationExceptionHandler* getInvocationExceptionHandler();
                    
                    virtual void setInvocationExceptionHandler(JIInvocationExceptionHandler*);
                    
                    virtual void unexport();

                    virtual void addLifecycle(JILifecycle* lifecycle);
                    
                    virtual void removeLifecycle(JILifecycle* lifecycle);
                    
                    virtual void addGCClientListener(JIGCClientListener* gcClientListener);
                    
                    virtual void removeGCClientListener(JIGCClientListener* gcClientListener);
                    
                    virtual void addInvocationListener(JIInvocationListener* i);
                    
                    virtual void removeInvocationListener(JIInvocationListener* i);

                    virtual void doExport(JObjectInformation* objectInformation, JEndPoint* endPoint);
                    
                    virtual void unexport(JObjectInformation* objectInformation);
                    
                    virtual void doExport(JObjectInformation* objectInformation);
                    
                    virtual void unexport(JObjectInformation* objectInformation, JEndPoint* endPoint);

                    virtual void objectAlive(JEndPoint* endPoint, JPrimitiveObjectArray* objects);

                    virtual void objectDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects);

                    virtual void objectDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects, JThrowable* throwable);

                    virtual void objectMaybeDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects, JThrowable* throwable);

                    virtual void invocationSucceeded(JObject* proxy, JMethod* method, JList* args);

                    virtual void invocationFailed(JObject* proxy, JMethod* method, JList* args, JThrowable* e);

                    virtual JString* toString();
                    
                    virtual ~JServer();
                };
            }
        }
    }
}
#endif
