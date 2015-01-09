#ifndef JCPP_RMI_SERVER_CONNECTION_JOBJECTINFORMATIONS_H
#define JCPP_RMI_SERVER_CONNECTION_JOBJECTINFORMATIONS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JTransport.h"
#include "jcpp/rmi/server/connection/JIInvocationListener.h"
#include "jcpp/rmi/server/connection/JMethodDigester.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"

using namespace jcpp::rmi::server::transport;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JServer;
                class JGCClient;
                class JGC;
                class JObjectInformation;
                class JILifecycle;
                class JMethodDigester;
                // @Class(canonicalName="jcpp.rmi.server.connection.ObjectInformations", simpleName="ObjectInformations");
                class JCPP_EXPORT JObjectInformations: public JObject{
                protected:
                    JMap* idMap;
                    JMap* objectMap;
                    JTransport* transport;
                    JILifecycle* lifecycle;
                    JIInvocationListener* invocationListener;
                    JServer* server;
                    JGC* gc;
                    JGCClient* gcClient;
                    JMethodDigester* methodDigester;

                public:
                    JObjectInformations(JILifecycle* lifecycle, JServer* server, JGC* gc, JGCClient* gcClient,JIInvocationListener* invocationListener);
                    
                    static JClass* getClazz();

                    virtual void setTransport(JTransport* transport);
                    
                    virtual JTransport* getTransport();
                    
                    virtual JServer* getServer();
                    
                    virtual JGC* getGC();
                    
                    virtual JGCClient* getGCClient();
                    
                    virtual JIInvocationListener* getInvocationListener();
                    
                    virtual JMethodDigester* getMethodDigester();
                    
                    virtual void doExport(JString* id, JObject* object, JList* interfaces);
                    
                    virtual JObjectInformation* unexport(JString* id);
                    
                    virtual JObjectInformation* unexport(JObject* object);
                    
                    virtual void unexport();
                    
                    virtual JPrimitiveObjectArray* list();
                    
                    virtual JObjectInformation* getObjectInformation(JString* id);
                    
                    virtual JObjectInformation* getObjectInformation(JObject* object);
                    
                    virtual JObjectInformation* remove(JString* id);
                    
                    virtual ~JObjectInformations();
                };
            }
        }
    }
}

#endif
