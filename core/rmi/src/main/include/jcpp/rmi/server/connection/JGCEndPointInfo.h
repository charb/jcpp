#ifndef JCPP_RMI_SERVER_CONNECTION_JGCENDPOINTINFO_H
#define JCPP_RMI_SERVER_CONNECTION_JGCENDPOINTINFO_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JObjectInformation.h"
#include "jcpp/rmi/server/connection/JGC.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JScheduledFuture.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::rmi::server::transport;
using namespace jcpp::util::concurrent;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JObjectInformation;
                class JGC;
                // @Class(canonicalName="jcpp.rmi.server.connection.GC$EndPointInfo", simpleName="GC$EndPointInfo");
                class JCPP_EXPORT JGCEndPointInfo : public JObject, public JRunnable{
                protected:
                    JGC* gc;
                    JMap* exportedObjects;
                    jbool bIsRunning;
                    jlong lastPingId;
                    jlong previousPingId;
                    JEndPoint* remoteEndPoint;
                    JScheduledFuture* scheduledFuture;

                public:
                    JGCEndPointInfo(JGC* gc,JEndPoint* remoteEndPoint);
                    
                    static JClass* getClazz();
                    
                    virtual jbool isUpdated();
                    
                    virtual JEndPoint* getRemoteEndPoint();
                    
                    virtual void doExport(JObjectInformation* objInfo);
                    
                    virtual void unexport(JObjectInformation* objInfo);
                    
                    virtual void unexport();
                    
                    virtual void update();
                    
                    virtual void ping(JPrimitiveBooleanArray* returnPing, JPrimitiveObjectArray* ids);
                    
                    virtual jbool isRunning();
                    
                    virtual void setRunning(jbool);
                    
                    virtual void run();
                    
                    virtual ~JGCEndPointInfo();
                };
            }
        }
    }
}
#endif
