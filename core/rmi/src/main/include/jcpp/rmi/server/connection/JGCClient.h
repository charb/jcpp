#ifndef JCPP_RMI_SERVER_CONNECTION_JGCCLIENT_H
#define JCPP_RMI_SERVER_CONNECTION_JGCCLIENT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JGCEndPointInfo.h"
#include "jcpp/rmi/server/connection/JGCClientEndPointInfo.h"
#include "jcpp/rmi/server/connection/JIGCClientListener.h"
#include "jcpp/rmi/server/connection/JIGCClient.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::util;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JGCClientEndPointInfo;
                // @Class(canonicalName="jcpp.rmi.server.connection.GCClient", simpleName="GCClient");
                class JCPP_EXPORT JGCClient : public JObject, public JIGCClient{
                    protected:
                        JMap* endPointInfos;
                        JIGCClientListener* gcClientListener;
                        JServer* localServer;

                    public:
                        JGCClient(JServer* localServer, JIGCClientListener* gcClientListener);
                        
                        static JClass* getClazz();
                        
                        virtual JPrimitiveObjectArray* getEndPoints();
                        
                        virtual void add(JMap* objectPointers);
                        
                        virtual void remove(JEndPoint* endPoint);
                        
                        virtual void unexport();
                        
                        virtual JIGCClientListener* getGCClientListener();
                        
                        virtual ~JGCClient();
                };
            }
        }
    }
}
#endif
