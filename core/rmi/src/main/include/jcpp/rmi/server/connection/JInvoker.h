#ifndef JCPP_RMI_SERVER_CONNECTION_JINVOKER_H
#define JCPP_RMI_SERVER_CONNECTION_JINVOKER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/util/JList.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.Invoker", simpleName="Invoker");
                class JCPP_EXPORT JInvoker : public JObject, public JSerializable{
            		private:
            			static const jlong serialVersionUID = -5888955964943945437LL;

                    protected:
                        //@Transient()
                        JObjectInformations* objectInformations;
                        JObjectPointer* objectPointer;
                        JPrimitiveBoolean* useInvocationQueue;
                        friend class JInvokerClass;

                    public:
                        JInvoker();
                        
                        JInvoker(JObjectInformations* objectInformations, JObjectPointer* objectPointer);
                        
                        static JClass* getClazz();
                        
                        virtual void setObjectPointer(JObjectPointer* o);
                        
                        virtual JObjectPointer* getObjectPointer();
                        
                        virtual void setObjectInformations(JObjectInformations* objectInformations);
                        
                        virtual JObjectInformations* getObjectInformations();
                        
                        virtual JObject* invoke(JMethod* method, JList* args);
                        
                        virtual ~JInvoker();
                };
            }
        }
    }
}
#endif
