#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{


                JEndPoint::JEndPoint():JObject(getClazz()){
                    this->site=null;
                    this->address=null;
                }

                JEndPoint::JEndPoint(JDataInputStream* in):JObject(getClazz()){
                    JString* host=in->readUTF();
                    jint port=in->readInt();
                    this->site=in->readUTF();
                    this->address=new JAddress();
                }

                JEndPoint::JEndPoint(JAddress* a, JString* s):JObject(getClazz()){
                    this->address=a;
                    this->site=s;
                }

                jbool JEndPoint::equals(JObject* other){
                    if (other->getClass()!=getClazz()){
                        return false;
                    }
                    JEndPoint* s=dynamic_cast<JEndPoint*>(other);
                    return s->address->equals(address) && s->site->equals(site);
                }

                void JEndPoint::write(JDataOutputStream* out){
                    out->writeUTF(address->getHostName());
                    out->writeInt(address->getPort());
                    out->writeUTF(site);
                }

                void JEndPoint::setAddress(JAddress* a){
                    this->address=a;
                }

                JAddress* JEndPoint::getAddress(){
                    return address;
                }

                void JEndPoint::setSite(JString* site){
                    this->site=site;
                }

                JString* JEndPoint::getSite(){
                    return site;
                }

                jint JEndPoint::hashCode(){
                    jint h=0;
                    if (address!=null){
                        if (address->getHostName()!=null){
                            h+=address->getHostName()->hashCode();
                        }
                        h+=address->getPort();
                    }
                    if (site!=null){
                        h+=site->hashCode();
                    }
                    return h;
                }

                JString* JEndPoint::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("EndPoint[")
                           ->append(address->toString())
                           ->append(":")
                           ->append(site)
                           ->append("]");
                    return builder->toString();
                }

                JEndPoint::~JEndPoint(){
                }
            }
        }
    }
}
