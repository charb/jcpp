#include "jcpp/rmi/server/gateway/JGatewayCompressionOutputStream.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{


                JGatewayCompressionOutputStream::JGatewayCompressionOutputStream(JOutputStream* out,JRoute* route):JFilterOutputStream(out,getClazz()){
                    this->gatewayOutputStream=new JGatewayOutputStream(out,route);
                }

                JRoute* JGatewayCompressionOutputStream::getRoute(){
                    return gatewayOutputStream->getRoute();
                }

                void JGatewayCompressionOutputStream::close(){
                    gatewayOutputStream->close();
                    out->close();
                }

                JGatewayCompressionOutputStream::~JGatewayCompressionOutputStream(){
                }
            }
        }
    }
}



