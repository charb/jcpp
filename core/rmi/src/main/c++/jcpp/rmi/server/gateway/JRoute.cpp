#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/util/JCollection.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{

                JRoute::JRoute():JObject(getClazz()){
                    this->addressList=new JArrayList(0);
                    this->isHttp=new JPrimitiveBoolean();
                }

                JRoute::JRoute(JRoute* route):JObject(getClazz()){
                    this->addressList=new JArrayList(0);
                    addressList->addAll(reinterpret_cast<JCollection*>(route->addressList));
                    this->isHttp=new JPrimitiveBoolean(route->isHttp->get());
                }

                jbool JRoute::equals(JObject* other){
                    if (other->getClass()!=getClazz()){
                        return false;
                    }
                    JRoute* s=dynamic_cast<JRoute*>(other);
                    return s->addressList->equals(addressList) && s->isHttp->get()==isHttp->get();
                }

                void JRoute::setIsHttp(jbool h){
                    isHttp->set(h);
                }

                jbool JRoute::getIsHttp(){
                    return isHttp->get();
                }

                void JRoute::addAddress(JAddress* a){
                    addressList->add(a);
                }

                void JRoute::removeAddress(JAddress* a){
                    addressList->remove(a);
                }

                JArrayList* JRoute::getAddressList(){
                    return addressList;
                }

                void JRoute::setAddressList(JArrayList* al){
                    this->addressList=al;
                }

                JAddress* JRoute::peakAddress(){
                    if (addressList->size() > 0) {
                        return (JAddress*)addressList->get(0);
                    }
                    return null;
                }

                JAddress* JRoute::popAddress(){
                    if (addressList->size() > 0) {
                        JAddress* a=(JAddress*)addressList->remove(0);
                        return a;
                    }
                    return null;
                }

                void JRoute::pushAddress(JAddress* a){
                    addressList->add(0,a);
                }

                jint JRoute::addressSize(){
                    return addressList->size();
                }

                void JRoute::clearAddress(){
                    addressList->clear();
                }

                JRoute* JRoute::clone(){
                    return new JRoute(this);
                }

                JString* JRoute::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("AddressList[")->append(addressList)
                           ->append("][IsHttp:")->append(isHttp->get())->append("]");
                    return builder->toString();
                }

                JRoute::~JRoute(){
                }
            }
        }
    }
}

