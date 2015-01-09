#ifndef JCPP_RMI_SERVER_CONNECTION_JIINVOCATIONEXCEPTIONHANDLER_H
#define JCPP_RMI_SERVER_CONNECTION_JIINVOCATIONEXCEPTIONHANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IInvocationExceptionHandler", simpleName="IInvocationExceptionHandler");
                class JCPP_EXPORT JIInvocationExceptionHandler : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JThrowable* handleException(JObject* object, JMethod* method, JPrimitiveObjectArray* args, JThrowable* exception)=0;

                    virtual ~JIInvocationExceptionHandler();
                };
            }
        }
    }
}

#endif
