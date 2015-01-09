#include "jcpp/rmi/server/transport/JTransportConfiguration.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{


                JTransportConfiguration::JTransportConfiguration():JObject(getClazz()){
                    this->gatewayConfiguration=new JGatewayConfiguration();
                    this->connectionPoolTimeout=new JLong(DEFAULT_CONNECTION_POOL_TIMEOUT);
                    this->socketTimeout=new JInteger(DEFAULT_SOCKET_TIMEOUT);
                    this->pingTimeout=new JInteger(DEFAULT_PING_TIMEOUT);
                    this->limitedSocketTimeout=new JInteger(LIMITED_SOCKET_TIMEOUT);
                    this->timeoutTimerInterval=new JLong(TIMEOUT_TIMER_INTERVAL);
                }

                JTransportConfiguration::JTransportConfiguration(JGatewayConfiguration* gatewayConfiguration, JLong* connectionTimeout, JInteger* socketTimeout, JInteger* pingTimeout, JInteger* limitedSocketTimeout, JLong* timeoutTimerInterval):JObject(getClazz()){
                    this->gatewayConfiguration=gatewayConfiguration;
                    this->connectionPoolTimeout=connectionTimeout;
                    this->socketTimeout=socketTimeout;
                    this->pingTimeout=pingTimeout;
                    this->limitedSocketTimeout=limitedSocketTimeout;
                    this->timeoutTimerInterval=timeoutTimerInterval;
                }

                JGatewayConfiguration* JTransportConfiguration::getGatewayConfiguration(){
                    return gatewayConfiguration;
                }

                void JTransportConfiguration::setGatewayConfiguration(JGatewayConfiguration* gatewayConfiguration){
                    this->gatewayConfiguration=gatewayConfiguration;
                }

                JLong* JTransportConfiguration::getConnectionPoolTimeout(){
                    return connectionPoolTimeout;
                }

                void JTransportConfiguration::setConnectionPoolTimeout(JLong* connectionTimeout){
                    this->connectionPoolTimeout=connectionTimeout;
                }

                JInteger* JTransportConfiguration::getSocketTimeout(){
                    return socketTimeout;
                }

                void JTransportConfiguration::setSocketTimeout(JInteger* socketTimeout){
                    this->socketTimeout=socketTimeout;
                }

                JInteger* JTransportConfiguration::getLimitedSocketTimeout(){
                    return limitedSocketTimeout;
                }

                void JTransportConfiguration::setLimitedSocketTimeout(JInteger* limitedSocketTimeout){
                    this->limitedSocketTimeout=limitedSocketTimeout;
                }

                JInteger* JTransportConfiguration::getPingTimeout(){
                    return pingTimeout;
                }

                void JTransportConfiguration::setPingTimeout(JInteger* pingTimeout){
                    this->pingTimeout=pingTimeout;
                }

                JLong* JTransportConfiguration::getTimeoutTimerInterval(){
                    return timeoutTimerInterval;
                }

                void JTransportConfiguration::setTimeoutTimerInterval(JLong* timeoutTimerInterval){
                    this->timeoutTimerInterval=timeoutTimerInterval;
                }

                JTransportConfiguration::~JTransportConfiguration(){
                }
            }
        }
    }
}

