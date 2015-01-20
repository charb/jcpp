#ifndef JCPP_RMI_SERVER_CONNECTION_JOBJECTHANDLER_H
#define JCPP_RMI_SERVER_CONNECTION_JOBJECTHANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/lang/reflect/JInvocationHandler.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/rmi/server/connection/JIInvocationListener.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                class JInvoker;
                class JObjectInformations;

                // @Class(canonicalName="jcpp.rmi.server.connection.ObjectHandler", simpleName="ObjectHandler");
                class JCPP_EXPORT JObjectHandler: public JObject, public JInvocationHandler, public JSerializable, public JCloneable{
                private:
                	static const jlong serialVersionUID = 3179670252394270616LL;

                protected:
                    JInvoker* invoker;
                    JObject* proxy;
                    //@Transient()
                    JClassLoader* classLoader;
                    JList* interfaces;
                    //@Transient()
                    JIInvocationListener* invocationListener;

                public:
                    JObjectHandler();

                    JObjectHandler(JObjectInformations* objectInformations,JClassLoader* classLoader, JList* interfaces, JObjectPointer* objectPointer);
                    
                    static JClass* getClazz();
                    
                    virtual JObject* getProxy();
                    
                    virtual JInvoker* getInvoker();
                    
                    virtual JClassLoader* getClassLoader();
                    
                    virtual JList* getInterfaces();
                    
                    virtual JObject* invoke(JObject* proxy, JMethod* method, JList* args);

                    virtual void setObjectInformations(JObjectInformations* objectInformations);
                    
                    virtual JString* toString();
                    
                    virtual jint hashCode();
                    
                    virtual jbool equals(JObject *o);
                    
                    virtual JObject* clone();
                    
                    virtual ~JObjectHandler();
                };
            }
        }
    }
}
#endif
