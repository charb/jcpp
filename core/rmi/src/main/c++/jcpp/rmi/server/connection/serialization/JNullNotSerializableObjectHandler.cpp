#include "jcpp/rmi/server/connection/serialization/JNullNotSerializableObjectHandler.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                namespace serialization{

                    JNullNotSerializableObjectHandler::JNullNotSerializableObjectHandler():JObject(getClazz()){
                    }

                    JObject* JNullNotSerializableObjectHandler::handleNotSerializableObject(JObject*){
                        return null;
                    }

                    JNullNotSerializableObjectHandler::~JNullNotSerializableObjectHandler(){
                    }
                }
            }
        }
    }
}


