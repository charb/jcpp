#include "jcpp/rmi/server/connection/JObjectPointer.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{


                JObjectPointer::JObjectPointer():JObject(getClazz()){
                    this->id=null;
                    this->endPoint=null;
                }

                JObjectPointer::JObjectPointer(JEndPoint* endPoint, JString* id):JObject(getClazz()){
                    this->endPoint=endPoint;
                    this->id=id;
                }

                jbool JObjectPointer::equals(JObject* other){
                    if (other->getClass()!=getClazz()){
                        return false;
                    }
                    JObjectPointer* s=dynamic_cast<JObjectPointer*>(other);
                    return s->endPoint->equals(endPoint) && s->id->equals(id);
                }

                JEndPoint* JObjectPointer::getEndPoint(){
                    return endPoint;
                }

                void JObjectPointer::setEndPoint(JEndPoint* endPoint){
                    this->endPoint=endPoint;
                }

                JString* JObjectPointer::getId(){
                    return id;
                }

                void JObjectPointer::setId(JString* id){
                    this->id=id;
                }

                jint JObjectPointer::hashCode(){
                    jint h=1;
                    h=h*31+id->hashCode();
                    h=h*31+endPoint->hashCode();
                    return h;
                }

                JString* JObjectPointer::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("ObjectPointer[")
                           ->append(endPoint)
                           ->append("[Id:")
                           ->append(id)
                           ->append("]]");
                    return builder->toString();
                }

                JObjectPointer::~JObjectPointer(){
                }
            }
        }
    }
}

