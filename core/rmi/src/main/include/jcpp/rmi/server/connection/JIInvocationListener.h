#ifndef JCPP_RMI_SERVER_CONNECTION_JIINVOCATIONLISTENER_H
#define JCPP_RMI_SERVER_CONNECTION_JIINVOCATIONLISTENER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/reflect/JMethod.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IInvocationListener", simpleName="IInvocationListener");
                class JCPP_EXPORT JIInvocationListener : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void invocationSucceeded(JObject* proxy, JMethod* method, JList* args)=0;

                    virtual void invocationFailed(JObject* proxy, JMethod* method, JList* args, JThrowable* e)=0;

                    virtual ~JIInvocationListener();
                };
            }
        }
    }
}

#endif
