#include "jcpp/rmi/server/connection/JObjectHandler.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/rmi/server/connection/JInvoker.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{


                JObjectHandler::JObjectHandler():JObject(getClazz()){
                    this->invoker=null;
                    this->proxy=null;
                    this->classLoader=null;
                    this->pinterfaces=null;
                    this->invocationListener=null;
                }

                JObjectHandler::JObjectHandler(JObjectInformations* objectInformations,JClassLoader* classLoader,JList* interfaces, JObjectPointer* objectPointer):JObject(getClazz()){
                    this->classLoader=classLoader;
                    this->invoker = new JInvoker(objectInformations, objectPointer);
                    this->proxy = JProxy::newProxyInstance(classLoader,interfaces, this);
                    this->pinterfaces = interfaces;
                    this->invocationListener = objectInformations->getInvocationListener();
                }

                JObject* JObjectHandler::getProxy(){
                    return proxy;
                }

                JInvoker* JObjectHandler::getInvoker(){
                    return invoker;
                }

                JClassLoader* JObjectHandler::getClassLoader(){
                    return classLoader;
                }

                JList* JObjectHandler::getInterfaces(){
                    return pinterfaces;
                }

                //TODO what to do for Object methods (toString, equals, hashcode,...)
                JObject* JObjectHandler::invoke(JObject* proxy, JMethod* method, JList* args){
                    if (method->getDeclaringClass()!=null && method->getDeclaringClass()->equals(JObject::getClazz())) {
                        if (method->getName()->equals(new JString("toString"))) {
                            return toString();
                        }
                        if (method->getName()->equals(new JString("hashCode"))) {
                            return new JPrimitiveLong(hashCode());
                        }
                        if (method->getName()->equals(new JString("equals"))) {
                            return new JPrimitiveBoolean(equals(args->get(0)));
                        }
                    }
                    JObject* invocationResult = null;
                    try {
                        invocationResult = invoker->invoke(method, args);
                        invocationListener->invocationSucceeded(proxy, method, args);
                    } catch (JThrowable* e) {
                        invocationListener->invocationFailed(proxy, method, args, e);
                        throw e;
                    }
                    return invocationResult;
                }

                void JObjectHandler::setObjectInformations(JObjectInformations* objectInformations){
                    invoker->setObjectInformations(objectInformations);
                    invocationListener = objectInformations->getInvocationListener();
                }

                JString* JObjectHandler::toString(){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Proxy[")
                           ->append(invoker->getObjectPointer())
                           ->append(", Interfaces[");
                    
                    if (getInterfaces()!=null && getInterfaces()->size()>0){
                        for (jint i = 0; i < (getInterfaces()->size() - 1); i++) {
                            JClass* c=dynamic_cast<JClass*>(getInterfaces()->get(i));
                            builder->append(c->getName())->append(", ");
                        }
                        JClass* c=dynamic_cast<JClass*>(getInterfaces()->get(getInterfaces()->size()-1));
                        builder->append(c->getName());
                    }
                    builder->append("]]");
                    return builder->toString();
                }

                jint JObjectHandler::hashCode(){
                    return invoker->getObjectPointer()->hashCode();
                }

                jbool JObjectHandler::equals(JObject *o){
                    if (o->getClass()->isProxy()){
                        JProxy* p=dynamic_cast<JProxy*>(o);
                        JInvocationHandler* invocationHandler = p->getInvocationHandler();
                        JObject* oih=dynamic_cast<JObject*>(invocationHandler);
                        if (oih->isInstanceOf(JObjectHandler::getClazz())){
                            JObjectHandler* objectHandler = dynamic_cast<JObjectHandler*>(oih);
                            JObjectPointer* objectPointer = objectHandler->getInvoker()->getObjectPointer();
                            return invoker->getObjectPointer()->equals(objectPointer);
                        }
                    }
                    return false;
                }

                JObject* JObjectHandler::clone(){
                    JObjectHandler* objectHandler = new JObjectHandler(invoker->getObjectInformations(), classLoader, getInterfaces(), invoker->getObjectPointer());
                    return objectHandler;
                }

                JObjectHandler::~JObjectHandler(){
                }
            }
        }
    }
}
