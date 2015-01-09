#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{



                JAddress::JAddress():JObject(getClazz()){
                    this->hostName=null;
                    this->port=new JPrimitiveInt();
                }

                JAddress::JAddress(JString* host, jint port):JObject(getClazz()){
                    this->hostName=host;
                    this->port=new JPrimitiveInt(port);
                }

                JAddress::JAddress(JAddress* adr):JObject(getClazz()){
                    this->hostName=adr->hostName;
                    this->port=new JPrimitiveInt(adr->port->get());
                }

                jbool JAddress::equals(JObject* other){
                    if (other->getClass()!=getClazz()){
                        return false;
                    }
                    JAddress* s=dynamic_cast<JAddress*>(other);
                    return s->hostName->equals(hostName) && s->port->get()==port->get();
                }

                void JAddress::setHostName(JString* host){
                    hostName=host;
                }

                JString* JAddress::getHostName(){
                    return hostName;
                }

                void JAddress::setPort(jint port){
                    this->port->set(port);
                }

                jint JAddress::getPort(){
                    return port->get();
                }

                jint JAddress::hashCode(){
                    return (hostName!=null?hostName->hashCode()*37+port->get():port->get());
                }

                JAddress* JAddress::clone(){
                    JAddress* a=new JAddress(this);
                    return a;
                }

                JString* JAddress::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Address[")->append(hostName)
                           ->append(":")->append(port)->append("]");
                    return builder->toString();
                }

                JAddress::~JAddress(){
                }
            }
        }
    }
}
