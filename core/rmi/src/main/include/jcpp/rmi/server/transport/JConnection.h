#ifndef JCPP_RMI_SREVER_TRANSPORT_JCONNECTION_H
#define JCPP_RMI_SREVER_TRANSPORT_JCONNECTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/rmi/server/transport/JConnections.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"

using namespace jcpp::rmi::server::gateway;
using namespace jcpp::net;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
                class JConnections;
                class JTransport;

                // @Class(canonicalName="jcpp.rmi.server.transport.Connection", simpleName="Connection");
                class JCPP_EXPORT JConnection : public JObject{
                    protected:
                        jlong lastUsed;
                        JConnections* connections;
                        JDataOutputStream* out;
                        JDataInputStream* in;
                        jbool opened;
                        JTransport* transport;
                        JGatewayConfiguration* gatewayConfiguration;
                        JRoute* route;
                        JConnection(JClass* _class,JRoute* route, JConnections* connections,JGatewayConfiguration* gatewayConfiguration);                        
                        JConnection(JClass* _class,JTransport* transport,JGatewayConfiguration* gatewayConfiguration);
                        virtual void sendConnectionHeader();
                        virtual void sendPing();
                        virtual jbool isSocketClosed()=0;   
                        virtual JOutputStream* getOuputStreamInternal()=0;
                        virtual JInputStream* getInputStreamInternal()=0;
                        virtual void killInternal()=0;
                        virtual JSocket* getSocketInternal()=0;

                    public:
                        
                        static JClass* getClazz();
                        
                        virtual void free();
                        
                        virtual void kill();
                        
                        virtual jbool openConnection();
                        
                        virtual void startCall();
                        
                        virtual void finishCall();
                        
                        virtual void sendOk();
                        
                        virtual jbool readOk();
                        
                        virtual jbool isDead();
                        
                        virtual JDataOutputStream* getOutputStream();
                        
                        virtual JDataInputStream* getInputStream();

                        virtual JGatewayConfiguration* getGatewayConfiguration();
                        
                        virtual void setLastUsed();
                        
                        virtual jbool isReusable();

                        virtual void setSoTimeout(jint timeout);
                        
                        virtual jlong getLastUsed();
                        
                        virtual JConnections* getConnections();
                        
                        virtual JString* toString();
                        
                        virtual ~JConnection();
                };
            }
        }
    }
}

#endif
