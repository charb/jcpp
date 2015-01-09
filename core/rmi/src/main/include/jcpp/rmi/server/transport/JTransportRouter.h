#ifndef JCPP_RMI_SERVER_TRANSPORT_JTRANSPORTROUTER_H
#define JCPP_RMI_SERVER_TRANSPORT_JTRANSPORTROUTER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JITransportRouter.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::util;
using namespace jcpp::rmi::server::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
            // @Class(canonicalName="jcpp.rmi.server.transport.TransportRouter", simpleName="TransportRouter");
                class JCPP_EXPORT JTransportRouter : public JObject, public JITransportRouter{
                    protected:
                        JMap* routes;

                    public:
                        JTransportRouter();
                        
                        static JClass* getClazz();
                        
                        virtual void addRoute(JString* localSite,JString* remoteSite, JRoute* route);
                        
                        virtual JRoute* findRoute(JString* localSite, JEndPoint* remoteEndpoint);
                        
                        virtual ~JTransportRouter();
                };
            }
        }
    }
}

#endif
