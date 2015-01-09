#ifndef JCPP_RMI_SERVER_CONNECTION_JOBJECTINFORMATION_H
#define JCPP_RMI_SERVER_CONNECTION_JOBJECTINFORMATION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JGCEndPointInfo.h"
#include "jcpp/rmi/server/connection/JILifecycle.h"
#include "jcpp/rmi/server/connection/JObjectHandler.h"
#include "jcpp/rmi/server/connection/JGC.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"

using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JILifecycle;
                class JObjectHandler;
                class JGC;
                class JObjectInformations;
                // @Class(canonicalName="jcpp.rmi.server.connection.ObjectInformation", simpleName="ObjectInformation");
                class JCPP_EXPORT JObjectInformation: public JObject{
                protected:
                    JString* id;
                    JObject* object;
                    JILifecycle* lifecycle;
                    JObjectHandler* objectHandler;
                    JMap* exportedEndPoints;
                    JObjectInformations* objectInformations;

                public:
                    JObjectInformation(JString* id, JObject* object, JList* interfaces, JObjectInformations* objectInformations, JILifecycle* lifecycle, JGC* gc);

                    static JClass* getClazz();

                    virtual JObject* getObject();
                    
                    virtual JString* getId();
                    
                    virtual JILifecycle* getLifecycle();
                    
                    virtual JObjectHandler* getObjectHandler();
                    
                    virtual void exported();
                    
                    virtual void doExport(JGCEndPointInfo* remoteEndPointInfo);
                    
                    virtual void unexport(JEndPoint* endPoint);
                    
                    virtual void unexport();
                    
                    virtual JString* toString();
                    
                    virtual ~JObjectInformation();
                };
            }
        }
    }
}

#endif
