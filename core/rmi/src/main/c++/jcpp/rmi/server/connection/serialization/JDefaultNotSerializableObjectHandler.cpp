#include "jcpp/rmi/server/connection/serialization/JDefaultNotSerializableObjectHandler.h"
#include "jcpp/io/JNotSerializableException.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                namespace serialization{

                    JDefaultNotSerializableObjectHandler::JDefaultNotSerializableObjectHandler():JObject(getClazz()){
                    }

                    JObject* JDefaultNotSerializableObjectHandler::handleNotSerializableObject(JObject* obj){
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Cannot serialize the object of type: ")
                               ->append(obj->getClass()->getName())
                               ->append(". Object: ")
                               ->append(obj);
                        return new JNotSerializableException(builder->toString());
                    }

                    JDefaultNotSerializableObjectHandler::~JDefaultNotSerializableObjectHandler(){
                    }
                }
            }
        }
    }
}

