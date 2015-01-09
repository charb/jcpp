#include "jcpp/rmi/server/gateway/JGatewayInputStream.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{


                JGatewayInputStream::JGatewayInputStream(JInputStream* in):JObjectInputStream(in){
                    route=dynamic_cast<JRoute*>(readObject());
                }

                JRoute* JGatewayInputStream::getRoute(){
                    return route;
                }

                JGatewayInputStream::~JGatewayInputStream(){
                }
            }
        }
    }
}
