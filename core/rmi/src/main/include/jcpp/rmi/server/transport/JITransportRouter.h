#ifndef JCPP_RMI_SERVER_TRANSPORT_JITRANSPORTROUTER_H
#define JCPP_RMI_SERVER_TRANSPORT_JITRANSPORTROUTER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"

using namespace jcpp::rmi::server::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
            // @Class(canonicalName="jcpp.rmi.server.transport.ITransportRouter", simpleName="ITransportRouter");
                class JCPP_EXPORT JITransportRouter : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JRoute* findRoute(JString* localSite, JEndPoint* remoteEndpoint)=0;

                    virtual ~JITransportRouter();
                };
            }
        }
    }
}

#endif
