#ifndef JCPP_RMI_SERVER_CONNECTION_JGC_H
#define JCPP_RMI_SERVER_CONNECTION_JGC_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectInformation.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JGCEndPointInfo.h"
#include "jcpp/rmi/server/connection/JIGC.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JScheduledExecutorService.h"

using namespace jcpp::util;
using namespace jcpp::util::concurrent;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JGCEndPointInfo;
                class JObjectInformation;
                // @Class(canonicalName="jcpp.rmi.server.connection.GC", simpleName="GC");
                class JCPP_EXPORT JGC : public JObject, public JIGC{
                    protected:
                        JConnectionConfiguration* connectionConfiguration;
                        JMap* endPointInfos;
                        JExecutorService* executorService;
                        JScheduledExecutorService* scheduledExecutorService;

                    public:
                        JGC(JExecutorService* executorService, JScheduledExecutorService* scheduledExecutorService, JConnectionConfiguration* connectionConfiguration);

                        static JClass* getClazz();
                        
                        virtual JPrimitiveObjectArray* getExportedEndPoints();
                        
                        virtual JScheduledExecutorService* getScheduledExecutorService();
                        
                        virtual JConnectionConfiguration* getConnectionConfiguration();
                        
                        virtual JPrimitiveBooleanArray* ping(JEndPoint* endPoint, JPrimitiveObjectArray* ids);

                        virtual void doExport(JList* objInfoSet, JEndPoint* endPoint);
                        
                        virtual void unexport(JEndPoint* endPoint);
                        
                        virtual void unexport();
                        
                        virtual void endPointDead(JEndPoint* endPoint);
                        
                        virtual void doExport(JObjectInformation* objInfo, JEndPoint* endPoint);
                        
                        virtual void remove(JEndPoint* e);
                        
                        virtual ~JGC();
                };
            }
        }
    }
}
#endif
