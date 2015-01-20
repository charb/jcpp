#ifndef JCPP_RMI_SERVER_CONNECTION_JMETHODDIGESTER_H
#define JCPP_RMI_SERVER_CONNECTION_JMETHODDIGESTER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/reflect/JMethod.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.MethodDigester", simpleName="MethodDigester");
                class JCPP_EXPORT JMethodDigester : public JObject{
                    protected:
                        static JPrimitiveObjectArray* array;
                        static JPrimitiveObjectArray* getArray();
                        JMap* digestToMethodMap;
                        JMap* methodToDigestMap;
                        void createDigests(JClass* classObject);

                    public:
                        JMethodDigester();

                        static JClass* getClazz();

                        virtual JMethod* getMethodFromDigest(JObject* object, jlong digest);
                        
                        virtual jlong getDigestFromMethod(JMethod* method);
                        
                        virtual JPrimitiveObjectArray* getMethods(JObject* object);
                        
                        virtual void clear();
                        
                        virtual ~JMethodDigester();
                };
            }
        }
    }
}
#endif
