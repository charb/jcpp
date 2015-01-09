#ifndef JCPP_RMI_SERVER_CONNECTION_JIREGISTRY_H
#define JCPP_RMI_SERVER_CONNECTION_JIREGISTRY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IRegistry", simpleName="IRegistry");
                class JCPP_EXPORT JIRegistry : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void bind(JString* id, JObject* object, JList* interfaces)=0;
                    
                    virtual JPrimitiveObjectArray* list()=0;

                    virtual JObject* lookup(JString* id)=0;

                    virtual void rebind(JString* id, JObject* object, JList* interfaces)=0;

                    virtual void unbind(JString* id)=0;

                    virtual ~JIRegistry();
                };
            }
        }
    }
}
#endif
