#ifndef JCPP_RMI_SERVER_CONNECTION_JIGCCLIENTLISTENER_H
#define JCPP_RMI_SERVER_CONNECTION_JIGCCLIENTLISTENER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IGCClientListener", simpleName="IGCClientListener");
                class JCPP_EXPORT JIGCClientListener : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void objectAlive(JEndPoint* endPoint, JPrimitiveObjectArray* objects)=0;

                    virtual void objectMaybeDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects, JThrowable* throwable)=0;

                    virtual void objectDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects,  JThrowable* throwable)=0;

                    virtual void objectDead(JEndPoint* endPoint, JPrimitiveObjectArray* objects)=0;

                    virtual ~JIGCClientListener();
                };
            }
        }
    }
}

#endif
