#ifndef JCPP_RMI_SERVER_CONNECTION_JCONNECTIONINPUTSTREAM_H
#define JCPP_RMI_SERVER_CONNECTION_JCONNECTIONINPUTSTREAM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::io;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.ConnectionInputStream", simpleName="ConnectionInputStream");
                class JCPP_EXPORT JConnectionInputStream : public JObjectInputStream{
                protected:
                    JObjectInformations* objectInformations;
                    JMap* gcObjectPointers;
                    JEndPoint* remoteEndPoint;

                public:
                    JConnectionInputStream(JInputStream* in, JObjectInformations* objectInformations, JEndPoint* remoteEndPoint);

                    static JClass* getClazz();

                    virtual void done();

                    virtual JObject* resolveObject(JObject* obj);

                    virtual ~JConnectionInputStream();
                };
            }
        }
    }
}

#endif
