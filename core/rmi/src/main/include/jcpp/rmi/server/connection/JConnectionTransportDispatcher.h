#ifndef JCPP_RMI_SERVER_CONNECTION_JCONNECTIONTRANSPORTDISPATCHER_H
#define JCPP_RMI_SERVER_CONNECTION_JCONNECTIONTRANSPORTDISPATCHER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/transport/JITransportDispatcher.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/util/JList.h"

using namespace jcpp::rmi::server::transport;
using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.ConnectionTransportDispatcher", simpleName="ConnectionTransportDispatcher");
                class JCPP_EXPORT JConnectionTransportDispatcher : public JObject, public JITransportDispatcher{
                protected:
                    JObjectInformations* objectInformations;

                public:
                    // @Class(canonicalName="jcpp.rmi.server.connection.ConnectionTransportDispatcher$InvocationResult", simpleName="ConnectionTransportDispatcher$InvocationResult");
                    class InvocationResult : public JObject{
                    protected:
                        JObject* object;
                        JMethod* method;
                        JObject* result;
                        jbool exceptionThrown;

                    public:
                        InvocationResult(JObject* object, JMethod* method, JObject* result, jbool exceptionThrown);

                        static JClass* getClazz();

                        virtual JObject* getObject();

                        virtual JMethod* getMethod();

                        virtual JObject* getResult();

                        virtual jbool isExceptionThrown();

                        virtual ~InvocationResult();
                    };

                    JConnectionTransportDispatcher(JObjectInformations* objectInformations);
                    
                    static JClass* getClazz();
                    
                    virtual void dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndPoint, JConnection* connection);
                    
                    virtual InvocationResult* invokeMethod(JString* id, jlong digest, JPrimitiveObjectArray* args, JEndPoint* endPoint);
                    
                    virtual ~JConnectionTransportDispatcher();
                };
            }
        }
    }
}
#endif
