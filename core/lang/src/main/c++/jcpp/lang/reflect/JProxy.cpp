#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/util/JList.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JMethod.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{
            static JObject* staticGetInvocationHandler(JObject* obj){
                JProxy* proxy=(JProxy*)obj;
                return dynamic_cast<JObject*>(proxy->getInvocationHandler());
            }

            static void staticSetInvocationHandler(JObject* obj,JObject* value){
                JProxy* proxy=(JProxy*)obj;
                proxy->setInvocationHandler(dynamic_cast<JInvocationHandler*>(value));
            }

            JObject** JProxy::JProxyClass::staticAdrInvocationHandler(JObject* obj){
                JProxy* proxy=(JProxy*)obj;
                JInvocationHandler** i=&proxy->h;
                return reinterpret_cast<JObject**>(i);
            }

            JProxy::JProxyClass::JProxyClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.reflect.Proxy");
                name=new JString("java.lang.reflect.Proxy");
                simpleName=new JString("Proxy");
                serialVersionUID=-2222568056686623797ULL;
            }

            void JProxy::JProxyClass::initialize(){
                addField(new JField(new JString("h"),JInvocationHandler::getClazz(),this,staticGetInvocationHandler,staticSetInvocationHandler,staticAdrInvocationHandler));
                addInterface(JSerializable::getClazz());
            }

            jcpp::lang::JClass* JProxy::JProxyClass::getSuperclass(){
                return JObject::getClazz();
            }

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JProxy::getClazz(){
                if (clazz==null){
                    clazz=new JProxyClass();
                }
                return clazz;
            }

            jcpp::lang::JClass* JProxy::getProxyClass(JClassLoader* loader,JList* interfaces){
                jcpp::lang::JClass* pc=null;
                for (jint i=0;i<interfaces->size();i++){
                    jcpp::lang::JClass* ci=dynamic_cast<jcpp::lang::JClass*>(interfaces->get(i));
                    try{
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append(ci->getName())->append("Proxy");
                        jcpp::lang::JClass* c=ci->getClassLoader()->loadClass(builder->toString());//TODO: maybe define getProxyClass in interfaces ...
                        if (JProxy::getClazz()->isAssignableFrom(c)){
                            pc=c;
                            break;
                        }
                    }catch(JThrowable* th){
                    }
                }
                return pc;
            }

            JProxy* JProxy::newProxyInstance(JClassLoader* loader,JList* interfaces, JInvocationHandler* ih){
                JProxy* proxy=null;
                jcpp::lang::JClass* pc=getProxyClass(loader,interfaces);
                if (pc!=null){
                    proxy=(JProxy*)pc->newInstance();
                    proxy->setInvocationHandler(ih);
                }
                if (proxy==null){
                    proxy=new JProxy(ih);
                }
                return proxy;
            }

            jbool JProxy::isProxyClass(jcpp::lang::JClass* cl){
                if (cl==null){
                    throw new JNullPointerException();
                }
                return cl->isProxy();
            }

            JInvocationHandler* JProxy::getInvocationHandler(JObject* proxy){
                if (!proxy->getClass()->isProxy()){
                    throw new JIllegalArgumentException(new JString("not a proxy instance"));
                }
                JProxy* p=dynamic_cast<JProxy*>(proxy);
                return p->getInvocationHandler();
            }

            JProxy::JProxy(jcpp::lang::JClass* _class):JObject(_class){
                this->h=null;
            }

            JProxy::JProxy():JObject(getClazz()){
                this->h=null;
            }

            JProxy::JProxy(JInvocationHandler* i):JObject(getClazz()){
                this->h=i;
            }

            JInvocationHandler* JProxy::getInvocationHandler(){
                return h;
            }

            void JProxy::setInvocationHandler(JInvocationHandler* h) {
                this->h = h;
            }

            JObject* JProxy::invoke(JString* methodName,JList* argTypes,JList* args){
                JMethod* jMethod=null;
                for (jint i=0;i<getClass()->getInterfaces()->size();i++){
                    jcpp::lang::JClass* jclass=dynamic_cast<jcpp::lang::JClass*>(getClass()->getInterfaces()->get(i));
                    if (jclass->hasMethod(methodName,argTypes)){
                        jMethod=jclass->getMethod(methodName,argTypes);
                        break;
                    }
                }
                if (jMethod==null){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("method ")->append(methodName)->append(" not declared in ")->append(toString());
                    throw new JNoSuchMethodException(builder->toString());
                }
                return h->invoke(this,jMethod,args);
            }            

            jint JProxy::hashCode(){
                JObject* myh=dynamic_cast<JObject*>(h);
                return myh->hashCode();
            }

            jbool JProxy::equals(JObject *o){
                if ((o == null) || o->getClass()!=getClass()){
                    return false;
                }
                JProxy* p=(JProxy*)o;
                JObject* myh=dynamic_cast<JObject*>(h);
                JObject* oyh=dynamic_cast<JObject*>(p->h);
                return myh->equals(oyh);
            }

            JString* JProxy::toString(){
                JStringBuilder* builder=new JStringBuilder();
                JObject* o=dynamic_cast<JObject*>(h);
                builder->append("Proxy[InvocationHandler:")->append(o->toString())->append("][Interfaces:");
                for (jint i=0;i<getClass()->getInterfaces()->size();i++){
                    jcpp::lang::JClass* jclass=dynamic_cast<jcpp::lang::JClass*>(getClass()->getInterfaces()->get(i));
                    builder->append(jclass->getName())->append(",");
                }
                builder->append("]");
                return builder->toString();
            }

            JProxy::~JProxy() {
            }
        }
    }
}
