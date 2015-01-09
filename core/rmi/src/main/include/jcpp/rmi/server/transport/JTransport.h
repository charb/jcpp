#ifndef JCPP_RMI_SREVER_TRANSPORT_JTRANSPORT_H
#define JCPP_RMI_SREVER_TRANSPORT_JTRANSPORT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/net/JServerSocket.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/transport/JConnections.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JScheduledExecutorService.h"
#include "jcpp/rmi/server/transport/JITransportRouter.h"
#include "jcpp/rmi/server/transport/JTransportConfiguration.h"
#include "jcpp/rmi/server/transport/JITransportDispatcher.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JSet.h"

using namespace jcpp::rmi::server::gateway;
using namespace jcpp::net;
using namespace jcpp::util::concurrent;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
                class JConnection;
                class JConnections;
                class JConnectionHeaderReader;

                // @Class(canonicalName="jcpp.rmi.server.transport.Transport", simpleName="Transport");
                class JCPP_EXPORT JTransport : public JObject, public JRunnable{
                    protected:
                        JSet* connectionReaders;
                        JExecutorService* executorService;
                        JFuture* future;
                        JEndPoint* localEndPoint;
                        JMap* remoteConnectionsMap;
                        JScheduledExecutorService* scheduledExecutorService;
                        JServerSocket* serverSocket;
                        JTransportConfiguration* transportConfiguration;
                        JITransportDispatcher* transportDispatcher;
                        JITransportRouter* transportRouter;

                    public:
                        JTransport(JEndPoint* localEndPoint,JITransportRouter* transportRouter,JITransportDispatcher* transportDispatcher,JExecutorService* executorService,JScheduledExecutorService* scheduledExecutorService,JTransportConfiguration* transportConfiguration);

                        static JClass* getClazz();

                        virtual JConnections* getConnections(JEndPoint* remoteEndPoint);
                        
                        virtual JEndPoint* getLocalEndPoint();
                        
                        virtual JScheduledExecutorService* getScheduledExecutorService();
                        
                        virtual JITransportDispatcher* getTransportDispatcher();
                        
                        virtual JITransportRouter* getTransportRouter();
                        
                        virtual JTransportConfiguration* getTransportConfiguration();
                        
                        virtual void startExport();
                        
                        virtual void run();
                        
                        virtual void stopExport();
                        
                        virtual void remove(JConnectionHeaderReader* reader);
                        
                        virtual void remove(JConnections* connections);
                        
                        virtual ~JTransport();
                };
            }
        }
    }
}



#endif
