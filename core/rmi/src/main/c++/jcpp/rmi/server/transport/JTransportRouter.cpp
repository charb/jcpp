#include "jcpp/rmi/server/transport/JTransportRouter.h"
#include "jcpp/util/JHashMap.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{

                JTransportRouter::JTransportRouter():JObject(getClazz()){
                    this->routes=new JHashMap();
                }

                void JTransportRouter::addRoute(JString* localSite,JString* remoteSite, JRoute* route){
                    synchronized(this,{
                        JMap* internalMap=dynamic_cast<JMap*>(routes->get(localSite));
                        if (internalMap==null){
                            internalMap=new JHashMap();
                            routes->put(localSite,dynamic_cast<JObject*>(internalMap));
                        }
                        internalMap->put(remoteSite,route);
                    })
                }

                JRoute* JTransportRouter::findRoute(JString* localSite, JEndPoint* remoteEndpoint){
                    synchronized(this,{
                        JRoute* route=null;
                        if (remoteEndpoint!=null){
                            if (localSite->equals(remoteEndpoint->getSite())){
                                route=new JRoute();
                                route->addAddress(new JAddress(remoteEndpoint->getAddress()));
                            }else{
                                JMap* internalMap=dynamic_cast<JMap*>(routes->get(localSite));
                                if (internalMap!=null){
                                    route=dynamic_cast<JRoute*>(internalMap->get(remoteEndpoint->getSite()));
                                    if (route!=null){
                                        route=route->clone();
                                        route->addAddress(new JAddress(remoteEndpoint->getAddress()));
                                    }
                                }
                            }
                        }
                        return route;
                    })
                }

                JTransportRouter::~JTransportRouter(){
                }
            }
        }
    }
}
