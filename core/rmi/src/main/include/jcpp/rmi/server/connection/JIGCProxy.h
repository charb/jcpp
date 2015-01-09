#ifndef JCPP_RMI_SERVER_CONNECTION_JIGCPROXY_H
#define JCPP_RMI_SERVER_CONNECTION_JIGCPROXY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JIGC.h"
#include "jcpp/lang/reflect/JProxy.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IGCProxy", simpleName="IGCProxy");
                class JCPP_EXPORT JIGCProxy : public JProxy, public JIGC{

                public:
                    JIGCProxy();

                    static JClass* getClazz();

                    virtual JPrimitiveBooleanArray* ping(JEndPoint* endPoint, JPrimitiveObjectArray* id);
                    
                    virtual void endPointDead(JEndPoint* endPoint);
                    
                    virtual JPrimitiveObjectArray* getExportedEndPoints();
                    
                    virtual ~JIGCProxy();
                };
            }
        }
    }
}

#endif
