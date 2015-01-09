#ifndef JCPP_RMI_SREVER_TRANSPORT_JTRANSPORTCONFIGURATION_H
#define JCPP_RMI_SREVER_TRANSPORT_JTRANSPORTCONFIGURATION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"

using namespace jcpp::io;
using namespace jcpp::rmi::server::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
            // @Class(canonicalName="jcpp.rmi.server.transport.TransportConfiguration", simpleName="TransportConfiguration");
                class JCPP_EXPORT JTransportConfiguration : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 721031819973449961LL;

                    protected:
                        JGatewayConfiguration* gatewayConfiguration;
                        JLong* connectionPoolTimeout;
                        JInteger* socketTimeout;
                        JInteger* pingTimeout;
                        JInteger* limitedSocketTimeout;
                        JLong* timeoutTimerInterval;


                    public:
                        static const jbyte MSG_TYPE_PING = (jbyte) 0x11;
                        static const jbyte MSG_TYPE_CALL = (jbyte) 0x21;
                        static const jbyte MSG_TYPE_OK = (jbyte) 0x31;
                        static const jbyte MSG_TYPE_EXCEPTION = (jbyte) 0x41;
                        static const jint MAGIC_NUMBER = 0x4d524d49;
                        static const jlong DEFAULT_CONNECTION_POOL_TIMEOUT = 60000 * 10;
                        static const jint DEFAULT_SOCKET_TIMEOUT = 24 * 3600 * 1000; // 24 hours
                        static const jint DEFAULT_PING_TIMEOUT = 30000;
                        static const jint LIMITED_SOCKET_TIMEOUT = 60000 * 3;
                        static const jlong TIMEOUT_TIMER_INTERVAL = 60000 * 5;

                        JTransportConfiguration();

                        JTransportConfiguration(JGatewayConfiguration* gatewayConfiguration, JLong* connectionTimeout, JInteger* socketTimeout, JInteger* pingTimeout, JInteger* limitedSocketTimeout, JLong* timeoutTimerInterval);

                        static JClass* getClazz();

                        virtual JGatewayConfiguration* getGatewayConfiguration();
                        
                        virtual void setGatewayConfiguration(JGatewayConfiguration* gatewayConfiguration);
                        
                        virtual JLong* getConnectionPoolTimeout();
                        
                        virtual void setConnectionPoolTimeout(JLong* connectionTimeout);
                        
                        virtual JInteger* getSocketTimeout();
                        
                        virtual void setSocketTimeout(JInteger* socketTimeout);
                        
                        virtual JInteger* getLimitedSocketTimeout();
                        
                        virtual void setLimitedSocketTimeout(JInteger* limitedSocketTimeout);
                        
                        virtual JInteger* getPingTimeout();
                        
                        virtual void setPingTimeout(JInteger* pingTimeout);
                        
                        virtual JLong* getTimeoutTimerInterval();
                        
                        virtual void setTimeoutTimerInterval(JLong* timeoutTimerInterval);
                        
                        virtual ~JTransportConfiguration();
                };
            }
        }
    }
}

#endif
