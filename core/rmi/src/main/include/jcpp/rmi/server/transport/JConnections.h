#ifndef JCPP_RMI_SREVER_TRANSPORT_JCONNECTIONS_H
#define JCPP_RMI_SREVER_TRANSPORT_JCONNECTIONS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/util/concurrent/JScheduledFuture.h"
#include "jcpp/util/JList.h"

using namespace jcpp::rmi::server::gateway;
using namespace jcpp::net;
using namespace jcpp::util::concurrent;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
                class JConnection;
                class JTransport;

                // @Class(canonicalName="jcpp.rmi.server.transport.Connections", simpleName="Connections");
                class JCPP_EXPORT JConnections : public JObject, public JRunnable{
                    protected:
                        JEndPoint* remoteEndPoint;
                        JList* freeConnectionList;
                        JList* takenConnectionList;
                        JTransport* transport;
                        jlong connectionTimeout;
                        JScheduledFuture* scheduledFuture;
                        virtual void remove();
                        virtual void launchTimeoutTimer();

                    public:
                        JConnections(JEndPoint* remoteEndPoint, JTransport* transport);

                        static JClass* getClazz();

                        virtual JConnection* createConnection();

                        virtual jlong getConnectionTimeout();
                        
                        virtual void freeAll();
                        
                        virtual void killAll();
                        
                        virtual JEndPoint* getRemoteEndPoint();
                        
                        virtual JTransport* getTransport();
                        
                        virtual void free(JConnection* connection);
                        
                        virtual void kill(JConnection* connection);
                        
                        virtual void run();
                        
                        virtual JString* toString();
                        
                        virtual ~JConnections();
                };
            }
        }
    }
}


#endif
