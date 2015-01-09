#include "jcpp/rmi/server/gateway/JGatewayCompressionInputStream.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{

                JGatewayCompressionInputStream::JGatewayCompressionInputStream(JInputStream* in,JGatewayConfiguration*):JFilterInputStream(in,getClazz()){
                    this->gatewayInputStream=new JGatewayInputStream(in);
                }

                JRoute* JGatewayCompressionInputStream::getRoute(){
                    return gatewayInputStream->getRoute();
                }

                JGatewayCompressionInputStream::~JGatewayCompressionInputStream(){
                }
            }
        }
    }
}


