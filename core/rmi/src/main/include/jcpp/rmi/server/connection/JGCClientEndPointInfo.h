#ifndef JCPP_RMI_SERVER_CONNECTION_JGCCLIENTENDPOINTINFO_H
#define JCPP_RMI_SERVER_CONNECTION_JGCCLIENTENDPOINTINFO_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/transport/JConnections.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/rmi/server/connection/JGCClient.h"
#include "jcpp/rmi/server/connection/JIGC.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JScheduledFuture.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"

using namespace jcpp::rmi::server::transport;
using namespace jcpp::util::concurrent;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.GCClient$EndPointInfo", simpleName="GCClient$EndPointInfo");
                class JCPP_EXPORT JGCClientEndPointInfo : public JObject, public JRunnable{
                protected:
                    JGCClient* gcClient;
                    JServer* localServer;
                    JIGC* gc;
                    jint gcExceptionCount;
                    jbool bIsRunning;
                    JMap* objects;
                    JEndPoint* remoteEndPoint;
                    JScheduledFuture* scheduledFuture;
                    JThrowable* throwable;
                    JConnections* connections;

                public:
                    JGCClientEndPointInfo(JGCClient* gcClient,JServer* localServer,JEndPoint* remoteEndPoint);
                    
                    static JClass* getClazz();
                    
                    virtual void doExport(JString* id, JObject* object);
                    
                    virtual void unexport(JString* id);
                    
                    virtual jbool ping();
                    
                    virtual void unexport();
                    
                    virtual jbool isRunning();
                    
                    virtual void setRunning(jbool);
                    
                    virtual JPrimitiveObjectArray* getObjects();
                    
                    virtual void run();
                    
                    virtual ~JGCClientEndPointInfo();
                };
            }
        }
    }
}
#endif
