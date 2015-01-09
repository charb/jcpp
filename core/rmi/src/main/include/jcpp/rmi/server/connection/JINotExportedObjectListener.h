#ifndef JCPP_RMI_SERVER_CONNECTION_JINOTEXPORTEDOBJECTLISTENER_H
#define JCPP_RMI_SERVER_CONNECTION_JINOTEXPORTEDOBJECTLISTENER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.INotExportedObjectListener", simpleName="INotExportedObjectListener");
                class JCPP_EXPORT JINotExportedObjectListener : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual jbool handleNotExportedObject(JObject* object)=0;

                    virtual ~JINotExportedObjectListener();
                };
            }
        }
    }
}

#endif
