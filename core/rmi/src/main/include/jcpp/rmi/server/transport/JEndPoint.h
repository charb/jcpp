#ifndef JCPP_RMI_SERVER_TRANSPORT_JENDPOINT_H
#define JCPP_RMI_SERVER_TRANSPORT_JENDPOINT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/io/JDataOutputStream.h"

using namespace jcpp::io;
using namespace jcpp::rmi::server::gateway;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace transport{
            // @Class(canonicalName="jcpp.rmi.server.transport.EndPoint", simpleName="EndPoint");
                class JCPP_EXPORT JEndPoint : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 1LL;

                    protected:
                        JAddress* address;
                        JString* site;

                    public:
                        JEndPoint();
                        
                        JEndPoint(JDataInputStream* in);
                        
                        JEndPoint(JAddress* a, JString* s);
                        
                        static JClass* getClazz();
                        
                        virtual void write(JDataOutputStream* out);
                        
                        virtual void setAddress(JAddress* a);
                        
                        virtual JAddress* getAddress();
                        
                        virtual void setSite(JString* site);
                        
                        virtual JString* getSite();
                        
                        virtual jbool equals(JObject* other);
                        
                        virtual jint hashCode();
                        
                        virtual JString* toString();

                        virtual ~JEndPoint();
                };
            }
        }
    }
}

#endif
