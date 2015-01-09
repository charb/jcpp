#ifndef JCPP_RMI_SERVER_JIGATEWAYLISTENER_H
#define JCPP_RMI_SERVER_JIGATEWAYLISTENER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.IGatewayListener", simpleName="IGatewayListener");
                class JCPP_EXPORT JIGatewayListener : public JInterface{
                public:
                    static JClass* getClazz();
                    
                    virtual void tunnelOpened()=0;
                    
                    virtual ~JIGatewayListener();
                };
            }
        }
    }
}

#endif
