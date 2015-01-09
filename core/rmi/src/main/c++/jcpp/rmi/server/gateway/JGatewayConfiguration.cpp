#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{

                JGatewayConfiguration::JGatewayConfiguration(JInteger* backLog, JInteger* receiveBufferSize, JInteger* sendBufferSize, JInteger* readTimeout, JInteger* connectionTimeout):JObject(getClazz()){
                    this->backLog=backLog;
                    this->receiveBufferSize=receiveBufferSize;
                    this->sendBufferSize=sendBufferSize;
                    this->readTimeout=readTimeout;
                    this->connectionTimeout=connectionTimeout;
                }

                JGatewayConfiguration::JGatewayConfiguration():JObject(getClazz()){
                    backLog=new JInteger(BACKLOG);
                    receiveBufferSize=new JInteger(RECEIVE_BUFFER_SIZE);
                    sendBufferSize=new JInteger(SEND_BUFFER_SIZE);
                    readTimeout=new JInteger(READ_TIMEOUT);
                    connectionTimeout=new JInteger(CONNECTION_TIME_OUT);
                }

                JInteger* JGatewayConfiguration::getBackLog(){
                    return backLog;
                }

                JInteger* JGatewayConfiguration::getReceiveBufferSize(){
                    return receiveBufferSize;
                }

                JInteger* JGatewayConfiguration::getSendBufferSize(){
                    return sendBufferSize;
                }

                JInteger* JGatewayConfiguration::getReadTimeout(){
                    return readTimeout;
                }

                JInteger* JGatewayConfiguration::getConnectionTimeout(){
                    return connectionTimeout;
                }

                void JGatewayConfiguration::setBackLog(JInteger* backLog){
                    this->backLog=backLog;
                }

                void JGatewayConfiguration::setReceiveBufferSize(JInteger* receiveBufferSize){
                    this->receiveBufferSize=receiveBufferSize;
                }

                void JGatewayConfiguration::setSendBufferSize(JInteger* sendBufferSize){
                    this->sendBufferSize=sendBufferSize;
                }

                void JGatewayConfiguration::setReadTimeout(JInteger* readTimeout){
                    this->readTimeout=readTimeout;
                }

                void JGatewayConfiguration::setConnectionTimeout(JInteger* connectionTimeout){
                    this->connectionTimeout=connectionTimeout;
                }

                JGatewayConfiguration::~JGatewayConfiguration(){
                }
            }
        }
    }
}

