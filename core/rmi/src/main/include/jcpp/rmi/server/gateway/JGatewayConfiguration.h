#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYCONFIGURATION_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYCONFIGURATION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewayConfiguration", simpleName="GatewayConfiguration");
                class JCPP_EXPORT JGatewayConfiguration : public JObject, JSerializable{
                private:
                	static const jlong serialVersionUID = 7816914239055009789LL;

                protected:
                    JInteger* backLog;
                    JInteger* receiveBufferSize;
                    JInteger* sendBufferSize;
                    JInteger* readTimeout;
                    JInteger* connectionTimeout;


                public:
                    static const jint BACKLOG = 4000;
                    static const jint RECEIVE_BUFFER_SIZE = 20480;
                    static const jint SEND_BUFFER_SIZE = 20480;
                    static const jint READ_TIMEOUT = 24 * 3600 * 1000; // 24 hours
                    static const jint CONNECTION_TIME_OUT = 60000;

                    JGatewayConfiguration(JInteger* backLog, JInteger* receiveBufferSize, JInteger* sendBufferSize, JInteger* readTimeout, JInteger* connectionTimeout);
                    
                    JGatewayConfiguration();
                    
                    static JClass* getClazz();

                    virtual JInteger* getBackLog();

                    virtual JInteger* getReceiveBufferSize();

                    virtual JInteger* getSendBufferSize();

                    virtual JInteger* getReadTimeout();

                    virtual JInteger* getConnectionTimeout();

                    virtual void setBackLog(JInteger* backLog);

                    virtual void setReceiveBufferSize(JInteger* receiveBufferSize);

                    virtual void setSendBufferSize(JInteger* sendBufferSize);

                    virtual void setReadTimeout(JInteger* readTimeout);

                    virtual void setConnectionTimeout(JInteger* connectionTimeout);

                    virtual ~JGatewayConfiguration();
                };
            }
        }
    }
}

#endif
