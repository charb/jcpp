#include "jcpp/rmi/server/connection/JInvoker.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/transport/JConnection.h"
#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/rmi/server/connection/JConnectionOutputStream.h"
#include "jcpp/rmi/server/connection/JConnectionInputStream.h"
#include "jcpp/io/JEOFException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JInvoker::JInvoker():JObject(getClazz()){
                    this->objectInformations=null;
                    this->objectPointer=null;
                    this->useInvocationQueue=new JPrimitiveBoolean(false);
                }

                JInvoker::JInvoker(JObjectInformations* objectInformations, JObjectPointer* objectPointer):JObject(getClazz()){
                    this->objectInformations=objectInformations;
                    this->objectPointer=objectPointer;
                    this->useInvocationQueue=new JPrimitiveBoolean(false);
                }

                void JInvoker::setObjectPointer(JObjectPointer* o){
                    this->objectPointer=o;
                }

                JObjectPointer* JInvoker::getObjectPointer(){
                    return objectPointer;
                }

                void JInvoker::setObjectInformations(JObjectInformations* objectInformations){
                    this->objectInformations=objectInformations;
                }

                JObjectInformations* JInvoker::getObjectInformations(){
                    return objectInformations;
                }

                JObject* JInvoker::invoke(JMethod* method, JList* args){
                    jlong digest = objectInformations->getMethodDigester()->getDigestFromMethod(method);
                    JConnections* connections = objectInformations->getTransport()->getConnections(objectPointer->getEndPoint());
                    JConnection* connection = connections->createConnection();
                    if (!connection->openConnection()) {
                        connection->kill();
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Unable to open a connection to ")
                               ->append(objectPointer->getEndPoint()->toString());
                        throw new JConnectionException(builder->toString());
                    }
                    connection->startCall();

                    JConnectionOutputStream* oos = new JConnectionOutputStream(connection->getOutputStream(), objectInformations, connection->getConnections()->getRemoteEndPoint());
                    oos->writeUTF(objectPointer->getId());
                    oos->writeLong(digest);
                    JPrimitiveObjectArray* array=(args!=null?args->toArray():null);
                    oos->writeObject(array);
                    connection->finishCall();
                    oos->done();

                    JObject* obj=null;
                    JThrowable* th=null;
                    JConnectionInputStream* ois = new JConnectionInputStream(connection->getInputStream(), objectInformations, objectPointer->getEndPoint());
                    jbyte exceptionCheck = ois->readByte();
                    if (exceptionCheck == JTransportConfiguration::MSG_TYPE_OK) {
                        obj = ois->readObject();
                        connection->readOk();

                    } else if (exceptionCheck == JTransportConfiguration::MSG_TYPE_EXCEPTION) {
                        th = dynamic_cast<JThrowable*>(ois->readObject());
                        connection->readOk();

                    } else {
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Invalid exception checking byte received while invoking method: ")
                               ->append(method->toString())
                               ->append(" on object: ")
                               ->append(objectPointer);

                        th=new JEOFException(builder->toString());
                    }

                    ois->done();
                    connection->free();//TODO always close it even after failure
                    if (th!=null){
                        throw th;
                    }
                    return obj;
                }

                JInvoker::~JInvoker(){
                }
            }
        }
    }
}

