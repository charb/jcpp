#ifndef JCPP_RMI_SERVER_CONNECTION_JILIFECYCLE_H
#define JCPP_RMI_SERVER_CONNECTION_JILIFECYCLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"

using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JObjectInformation;
                // @Class(canonicalName="jcpp.rmi.server.connection.ILifecylce", simpleName="ILifecycle");
                class JCPP_EXPORT JILifecycle : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void doExport(JObjectInformation* objectInformation)=0;

                    virtual void doExport(JObjectInformation* objectInformation, JEndPoint* endPoint)=0;

                    virtual void unexport(JObjectInformation* objectInformation,JEndPoint* endPoint)=0;

                    virtual void unexport(JObjectInformation* objectInformation)=0;

                    virtual ~JILifecycle();
                };
            }
        }
    }
}
#endif
