#ifndef JCPP_RMI_SREVER_TRANSPORT_JCONNECTIONHEADERREADER_H
#define JCPP_RMI_SREVER_TRANSPORT_JCONNECTIONHEADERREADER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/rmi/server/transport/JTransport.h"

using namespace jcpp::rmi::server::gateway;
using namespace jcpp::net;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
            // @Class(canonicalName="jcpp.rmi.server.transport.ConnectionHeaderReader", simpleName="ConnectionHeaderReader");
                class JCPP_EXPORT JConnectionHeaderReader : public JObject, public JRunnable{
                    protected:
                        JSocket* socket;
                        JTransport* transport;

                    public:
                        JConnectionHeaderReader(JSocket* socket, JTransport* transport);

                        static JClass* getClazz();

                        virtual void unexport();

                        virtual void run();

                        virtual ~JConnectionHeaderReader();
                };
            }
        }
    }
}


#endif
