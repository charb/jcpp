#include "jcpp/rmi/server/connection/JRegistry.h"
#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/rmi/server/connection/JObjectInformation.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JRegistry::JRegistry(JObjectInformations* objectInformations):JObject(getClazz()){
                    this->objectInformations=objectInformations;
                }

                void JRegistry::bind(JString* id, JObject* object, JList* interfaces){
                    if(object == null) {
                        throw new JConnectionException(new JString("Bind Error: Attempting to bind a null object"));
                    }
                    if(id == null) {
                        throw new JConnectionException(new JString("Bind Error: Attempting to bind an object with an invalid id."));
                    }
                    if(interfaces == null || interfaces->size()==0) {
                        throw new JConnectionException(new JString("Bind Error: Attempting to bind and object without any specified interfaces."));
                    }
                    JObjectInformation* objInfo = objectInformations->getObjectInformation(id);
                    if (objInfo == null) {
                        objectInformations->doExport(id, object, interfaces);
                    } else {
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Bind Error: Object already bound: ")
                               ->append(objInfo)
                               ->append(" at: ")
                               ->append(objectInformations->getTransport()->getLocalEndPoint());
                        throw new JConnectionException(builder->toString());
                    }
                }

                JPrimitiveObjectArray* JRegistry::list(){
                    return objectInformations->list();
                }

                JObject* JRegistry::lookup(JString* id){
                    JObjectInformation* objInfo = objectInformations->getObjectInformation(id);
                    if(objInfo == null) {
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Object of ID: ")
                               ->append(id)
                               ->append(" is not bound in registry at: ")
                               ->append(objectInformations->getTransport()->getLocalEndPoint());
                        throw new JConnectionException(builder->toString());
                    }
                    return objInfo->getObject();
                }

                void JRegistry::rebind(JString* id, JObject* object, JList* interfaces){
                    if(object == null) {
                        throw new JConnectionException(new JString("Bind Error: Attempting to bind a null object"));
                    }
                    if(id == null) {
                        throw new JConnectionException(new JString("Bind Error: Attempting to bind an object with an invalid id."));
                    }
                    if(interfaces == null || interfaces->size()==0) {
                        throw new JConnectionException(new JString("Bind Error: Attempting to bind and object without any specified interfaces."));
                    }
                    objectInformations->doExport(id, object,interfaces);
                }

                void JRegistry::unbind(JString* id){
                    if (objectInformations->unexport(id) == null) {
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Object of ID: ")
                               ->append(id)
                               ->append(" is not bound in registry at: ")
                               ->append(objectInformations->getTransport()->getLocalEndPoint());
                        throw new JConnectionException(builder->toString());
                    }
                }

                JRegistry::~JRegistry(){
                }
            }
        }
    }
}

