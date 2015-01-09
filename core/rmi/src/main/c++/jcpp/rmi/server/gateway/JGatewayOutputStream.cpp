#include "jcpp/rmi/server/gateway/JGatewayOutputStream.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{

                JGatewayOutputStream::JGatewayOutputStream(JOutputStream* out,JRoute* route):JObjectOutputStream(out){
                    this->route=route;
                    writeObject(route);
                    flush();
                }

                JRoute* JGatewayOutputStream::getRoute(){
                    return route;
                }

                JGatewayOutputStream::~JGatewayOutputStream(){
                }
            }
        }
    }
}

