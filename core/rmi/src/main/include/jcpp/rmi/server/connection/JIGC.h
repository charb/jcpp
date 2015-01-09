#ifndef JCPP_RMI_SERVER_CONNECTION_IGC_H
#define JCPP_RMI_SERVER_CONNECTION_IGC_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"

using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IGC", simpleName="IGC");
                class JCPP_EXPORT JIGC : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JPrimitiveBooleanArray* ping(JEndPoint* endPoint, JPrimitiveObjectArray* id)=0;

                    virtual void endPointDead(JEndPoint* endPoint)=0;

                    virtual JPrimitiveObjectArray* getExportedEndPoints()=0;

                    virtual ~JIGC();
                };
            }
        }
    }
}

#endif
