#ifndef JCPP_RMI_SERVER_CONNECTION_JCONNECTIONOUTPUTSTREAM_H
#define JCPP_RMI_SERVER_CONNECTION_JCONNECTIONOUTPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JList.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/serialization/JINotSerializableObjectHandler.h"
#include "jcpp/rmi/server/connection/JINotExportedObjectListener.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::rmi::server::transport;
using namespace jcpp::rmi::server::connection::serialization;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.ConnectionOutputStream", simpleName="ConnectionOutputStream");
                class JCPP_EXPORT JConnectionOutputStream : public JObjectOutputStream{
                protected:
                    JEndPoint* remoteEndPoint;
                    JObjectInformations* objectInformations;
                    JList* exportedObjInfos;

                public:
                    JConnectionOutputStream(JOutputStream* out, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint);

                    static JClass* getClazz();

                    virtual void done();

                    virtual JObject* replaceObject(JObject* obj);

                    virtual ~JConnectionOutputStream();
                };
            }
        }
    }
}
#endif
