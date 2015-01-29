#include "jcpp/rmi/server/connection/JConnectionTransportDispatcher.h"
#include "jcpp/rmi/server/connection/JConnectionInputStream.h"
#include "jcpp/rmi/server/connection/JConnectionOutputStream.h"
#include "jcpp/rmi/server/connection/JIInvocationExceptionHandler.h"
#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JConnectionTransportDispatcher::InvocationResult::InvocationResult(JObject* object, JMethod* method, JObject* result, jbool exceptionThrown):JObject(getClazz()){
                    this->object=object;
                    this->method=method;
                    this->result=result;
                    this->exceptionThrown=exceptionThrown;
                }

                JObject* JConnectionTransportDispatcher::InvocationResult::getObject(){
                    return object;
                }

                JMethod* JConnectionTransportDispatcher::InvocationResult::getMethod(){
                    return method;
                }

                JObject* JConnectionTransportDispatcher::InvocationResult::getResult(){
                    return result;
                }

                jbool JConnectionTransportDispatcher::InvocationResult::isExceptionThrown(){
                    return exceptionThrown;
                }

                JConnectionTransportDispatcher::InvocationResult::~InvocationResult(){
                }

                JConnectionTransportDispatcher::JConnectionTransportDispatcher(JObjectInformations* objectInformations):JObject(getClazz()){
                    this->objectInformations=objectInformations;
                }

                void JConnectionTransportDispatcher::dispatch(JEndPoint* fromEndPoint, JEndPoint* toEndPoint, JConnection* connection){
                    JConnectionInputStream* ois = new JConnectionInputStream(connection->getInputStream(), objectInformations, fromEndPoint);
                    JString* objectId = null;
                    jlong digest = 0;
                    JPrimitiveObjectArray* args = null;
                    JThrowable* readException = null;
                    try {
                        objectId = ois->readUTF();
                        digest = ois->readLong();
                        args = dynamic_cast<JPrimitiveObjectArray*>(ois->readObject());
                    } catch (JThrowable* e) {
                        readException = e;
                    }
                    ois->done();

                    JConnectionOutputStream* oos = new JConnectionOutputStream(connection->getOutputStream(), objectInformations, fromEndPoint);
                    try {
                        if (readException != null) {
                            throw readException;
                        }
                        InvocationResult* invocationResult = invokeMethod(objectId, digest, args , fromEndPoint);
                        JObject* result = invocationResult->getResult();
                        if (invocationResult->isExceptionThrown()) {
                            throw dynamic_cast<JThrowable*>(result);
                        }
                        oos->writeByte(JTransportConfiguration::MSG_TYPE_OK);
                        oos->writeObject(result);
                        connection->sendOk(); // for the Call

                    } catch (JThrowable* throwable) {
                        oos->writeByte(JTransportConfiguration::MSG_TYPE_EXCEPTION);
                        oos->writeObject(throwable);
                        oos->flush();
                        connection->sendOk(); // for the Call
                    }
                    try {
                        oos->done();
                    } catch (JThrowable* throwable) {
                        //TODO log
                        throwable->printStackTrace();
                    }
                }

                JConnectionTransportDispatcher::InvocationResult* JConnectionTransportDispatcher::invokeMethod(JString* id, jlong digest, JPrimitiveObjectArray* args, JEndPoint* endPoint){
                    JObject* object = null;
                    JMethod* method = null;
                    JObject* result = null;
                    jbool exceptionThrown = false;

                    JObjectInformation* objectInformation = objectInformations->getObjectInformation(id);
                    if (objectInformation == null) {
                        exceptionThrown = true;
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Object of ID: ")
                               ->append(id)
                               ->append(" has not been exported in ")
                               ->append(objectInformations->getTransport()->getLocalEndPoint());

                        result = new JConnectionException(builder->toString());

                    } else {
                        object = objectInformation->getObject();
                        method = objectInformations->getMethodDigester()->getMethodFromDigest(object, digest);
                        if (method == null) {
                            exceptionThrown = true;
                            JPrimitiveObjectArray* methods = objectInformations->getMethodDigester()->getMethods(object);
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append("No method found for digest: ")
                                   ->append(digest)
                                   ->append(" on object: ")
                                   ->append(object)
                                   ->append("\n")
                                   ->append("Methods available for type ")
                                   ->append(object->getClass()->toString())
                                   ->append(":\n");
                            for (jint i=0;i<methods->size();i++){
                                builder->append("\t")->append(methods->get(i))->append(";\n");
                            }
                            result = new JConnectionException(builder->toString());

                        } else {
                            try {
                                result = method->invoke(object, JArrays::asList(args));
                            } catch (JThrowable* e) {
                                exceptionThrown = true;
                                JIInvocationExceptionHandler* handler = objectInformations->getServer()->getInvocationExceptionHandler();
                                if (handler != null) {
                                    result = handler->handleException(object, method,args, e);
                                } else {
                                    result = e;
                                }
                            }
                        }
                    }
                    return new InvocationResult(object, method, result, exceptionThrown);
                }

                JConnectionTransportDispatcher::~JConnectionTransportDispatcher(){
                }
            }
        }
    }
}
