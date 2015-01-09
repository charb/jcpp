#include "jcpp/rmi/server/JRMIServerTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/net/JInetAddress.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/transport/JTransportRouter.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"
#include "jcpp/rmi/server/JRemoteSample.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::net;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::gateway;
using namespace jcpp::rmi::server::transport;
using namespace jcpp::rmi::server::connection;

namespace jcpp{
    namespace rmi{
        namespace server{

            JRMIServerTest::JRMIServerTest():JAbstractTest(getClazz(),new JString("test")){
            }

            void JRMIServerTest::test(JEndPoint* localEndPoint1,jbool w){
                try{
                    JRemoteSample* rs2=new JRemoteSample();

                    //initializing endpoint2                            
                    JAddress* adr2=new JAddress();
                    adr2->setHostName(JInetAddress::getLocalHost()->getHostName());
                    adr2->setPort(9998);
                    JEndPoint* localEndPoint2=new JEndPoint(adr2,new JString("site1"));

                    //initializing server2
                    JTransportRouter* router2=new JTransportRouter();
                    JConnectionConfiguration* cc2=new JConnectionConfiguration();
                    JServer* server2=new JServer(localEndPoint2,router2,cc2);

                    JList* i2=new JArrayList();
                    i2->add(JIRemoteSample::getClazz());
                    server2->getIRegistry()->bind(JIRemoteSample::getClazz()->getName(),rs2,i2);

                    JObject* obj=server2->lookup(localEndPoint1,JIRegistry::getClazz());
                    JSystem::out->print(new JString("Lookup returns =="));
                    JSystem::out->println(obj);

                    JProxy* proxy=dynamic_cast<JProxy*>(obj);
                    JObject* result=proxy->invoke(new JString("list"),null,null);
                    JSystem::out->print(new JString("List returns == "));
                    JSystem::out->println(result);
                    JPrimitiveObjectArray* ar=dynamic_cast<JPrimitiveObjectArray*>(result);
                    for (jint i=0;i<ar->size();i++){
                        JSystem::out->print(i);
                        JSystem::out->print(new JString("="));
                        JSystem::out->println(ar->get(i));

                        JSystem::out->print(i);
                        JSystem::out->print(new JString("="));
                        JSystem::out->println(ar->get(i)->getClass());
                    }

                    JIRegistry* regProxy=dynamic_cast<JIRegistry*>(obj);
                    for (jint j=0;j<1000;j++){
                        JSystem::out->print(new JString("Call ["));
                        JSystem::out->print(j);
                        JSystem::out->println(new JString("]:"));
                        result=regProxy->list();
                        JSystem::out->println(result->getClass()->getName());

                        ar=dynamic_cast<JPrimitiveObjectArray*>(result);
                        for (jint i=0;i<ar->size();i++){
                            JSystem::out->print(i);
                            JSystem::out->print(new JString("="));
                            JSystem::out->println(ar->get(i));

                            JSystem::out->print(i);
                            JSystem::out->print(new JString("="));
                            JSystem::out->println(ar->get(i)->getClass());
                        }
                    }

                    JObject* remoteObject=server2->lookup(localEndPoint1,JIRemoteSample::getClazz());
                    JSystem::out->print(new JString("RemoteObject->getClass()->getName()=="));
                    JSystem::out->println(remoteObject->getClass()->getName());

                    JSystem::out->print(new JString("RemoteObject=="));
                    JSystem::out->println(remoteObject);

                    JIRemoteSample* remoteSample=dynamic_cast<JIRemoteSample*>(remoteObject);
                    JSampleObject* so=remoteSample->getSampleObject();
                    JSystem::out->print(new JString("SampleObject=="));
                    JSystem::out->println(so);

                    JSystem::out->print(new JString("RemoteSample->getRemoteSample()=="));
                    JSystem::out->println(dynamic_cast<JObject*>(remoteSample->getRemoteSample()));

                    JIRemoteSample* rsample=remoteSample->getRemoteSample();
                    JObject* remoteSampleObject=dynamic_cast<JObject*>(rsample);
                    JSystem::out->print(new JString("RemoteSampleObject=="));
                    JSystem::out->println(remoteSampleObject);

                    JSystem::out->print(new JString("SampleObject->getRemoteSample()->getRemoteSample()=="));
                    JSystem::out->println(dynamic_cast<JObject*>(so->getRemoteSample()->getRemoteSample()));
                    so->getRemoteSample()->checkRemoteSample(so->getRemoteSample());

                    JSystem::out->println(new JString("check with pointer as param worked."));
                    JIRemoteSample* irs2=so->getRemoteSample();
                    JIRemoteSample* localrs2=dynamic_cast<JIRemoteSample*>(rs2);
                    JObject* oo2=dynamic_cast<JObject*>(irs2);
                    JSystem::out->print(new JString("SampleObject->getRemoteSample()->getClass()=="));
                    JSystem::out->println(oo2->getClass());

                    oo2=dynamic_cast<JObject*>(rs2);
                    JSystem::out->print(new JString("SampleObject->getRemoteSample()->getRemoteSample()=="));
                    JSystem::out->println(oo2->getClass());

                    JSystem::out->print(new JString("RemoteSample()->getSampleObject()=="));
                    JSystem::out->println(remoteSample->getSampleObject());

                    JSystem::out->println(new JString("Calling checkCallback"));
                    remoteSample->checkCallback(rs2);

                    if (w){
                        synchronized(this,{
                            wait();
                        })
                    }

                    server2->unexport();

                }catch(JThrowable* th){
                    th->printStackTrace();
                    throw th;
                }
            }

            void JRMIServerTest::test(){
                try{
                    JRemoteSample* rs=new JRemoteSample();

                    //initializing endpoint
                    JAddress* adr=new JAddress();
                    adr->setHostName(JInetAddress::getLocalHost()->getHostName());
                    adr->setPort(9875);
                    JEndPoint* localEndPoint1=new JEndPoint(adr,new JString("site1"));
                    
                    //initializing server
                    JTransportRouter* router1=new JTransportRouter();
                    JConnectionConfiguration* cc1=new JConnectionConfiguration();
                    JServer* server1=new JServer(localEndPoint1,router1,cc1);
                    
                    //exporting object
                    JList* i=new JArrayList();
                    i->add(JIRemoteSample::getClazz());
                    server1->getIRegistry()->bind(JIRemoteSample::getClazz()->getName(),rs,i);

                    test(localEndPoint1,false);
                    server1->unexport();


                    //initializing endpoint
                    adr->setPort(9876);
                    localEndPoint1=new JEndPoint(adr,new JString("site1"));
                    test(localEndPoint1,true);

                }catch(JThrowable* th){
                    th->printStackTrace();
                    throw th;
                }
            }

            JRMIServerTest::~JRMIServerTest(){
            }
        }
    }
}
