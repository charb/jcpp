#ifndef JCPP_RMI_SERVER_GATEWAY_JADDRESS_H
#define JCPP_RMI_SERVER_GATEWAY_JADDRESS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/io/JDataOutputStream.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.Address", simpleName="Address");
                class JCPP_EXPORT JAddress : public JObject, public JSerializable, public JCloneable{
                	private:
                		static const jlong serialVersionUID = 1LL;

                    protected:
                        JString* hostName;
                        JPrimitiveInt* port;

                    public:
                        JAddress();

                        JAddress(JString* host, jint port);

                        JAddress(JAddress* adr);

                        static JClass* getClazz();

                        virtual void setHostName(JString* host);
                        
                        virtual JString* getHostName();
                        
                        virtual void setPort(jint port);
                        
                        virtual jint getPort();
                                                
                        virtual jbool equals(JObject* other);
                        
                        virtual jint hashCode();
                        
                        virtual JAddress* clone();
                        
                        virtual JString* toString();

                        virtual ~JAddress();
                };
            }
        }
    }
}

#endif
