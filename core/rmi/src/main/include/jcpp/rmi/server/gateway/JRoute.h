#ifndef JCPP_RMI_SERVER_GATEWAY_JROUTE_H
#define JCPP_RMI_SERVER_GATEWAY_JROUTE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JString.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.Route", simpleName="Route");
                class JCPP_EXPORT JRoute : public JObject, public JSerializable, public JCloneable{
                	private:
                		static const jlong serialVersionUID = 2731749507109405573LL;

                    protected:
                        JArrayList* addressList;
                        JPrimitiveBoolean* isHttp;

                    public:
                        JRoute();

                        JRoute(JRoute* route);

                        static JClass* getClazz();

                        virtual void setIsHttp(jbool h);

                        virtual jbool getIsHttp();

                        virtual void addAddress(JAddress* a);

                        virtual void removeAddress(JAddress* a);

                        virtual JArrayList* getAddressList();

                        virtual void setAddressList(JArrayList* al);

                        virtual JAddress* peakAddress();

                        virtual JAddress* popAddress();

                        virtual void pushAddress(JAddress* a);

                        virtual jint addressSize();

                        virtual void clearAddress();

                        virtual jbool equals(JObject* other);

                        virtual JRoute* clone();

                        virtual JString* toString();

                        virtual ~JRoute();
                };
            }
        }
    }
}

#endif
