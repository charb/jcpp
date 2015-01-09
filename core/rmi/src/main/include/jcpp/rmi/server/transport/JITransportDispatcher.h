#ifndef JCPP_RMI_SREVER_TRANSPORT_JITRANSPORTDISPATCHER_H
#define JCPP_RMI_SREVER_TRANSPORT_JITRANSPORTDISPATCHER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/transport/JConnection.h"

using namespace jcpp::rmi::server::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
            // @Class(canonicalName="jcpp.rmi.server.transport.ITransportDispatcher", simpleName="ITransportDispatcher");
                class JCPP_EXPORT JITransportDispatcher : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndpoint,JConnection* connection)=0;

                    virtual ~JITransportDispatcher();
                };
            }
        }
    }
}

#endif
