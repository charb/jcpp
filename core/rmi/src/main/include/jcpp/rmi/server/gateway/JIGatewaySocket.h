#ifndef JCPP_RMI_SERVER_JIGATEWAYSOCKET_H
#define JCPP_RMI_SERVER_JIGATEWAYSOCKET_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/gateway/JRoute.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.IGatewaySocket", simpleName="IGatewaySocket");
                class JCPP_EXPORT JIGatewaySocket : public JInterface{
                public:
                    static JClass* getClazz();
                    
                    virtual JRoute* getRoute()=0;
                    
                    virtual jbool isReusable()=0;
                    
                    virtual ~JIGatewaySocket();
                };
            }
        }
    }
}

#endif
