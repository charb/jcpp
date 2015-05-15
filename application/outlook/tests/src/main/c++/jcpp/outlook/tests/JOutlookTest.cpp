#include "jcpp/outlook/tests/JOutlookTest.h"
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
#include "jcpp/outlook/server/JOutlook.h"

using namespace jcpp::lang;
using namespace jcpp::net;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::gateway;
using namespace jcpp::rmi::server::connection;
using namespace jcpp::rmi::server::transport;
using namespace jcpp::io;
using namespace junit::framework;
using namespace jcpp::outlook::server;
using namespace jcpp::util;

namespace jcpp{
    namespace outlook{
        namespace tests{

            JOutlookTest::JOutlookTest():JTestCase(getClazz(), new JString("test")) {
            }

            void JOutlookTest::test(){

                try{
                    //initializing endpoint
                    JAddress* adr=new JAddress();
                    adr->setHostName(JInetAddress::getLocalHost()->getHostName());
                    adr->setPort(9800);
                    JEndPoint* localEndPoint1=new JEndPoint(adr,new JString("site1"));

                    //initializing server
                    JTransportRouter* router1=new JTransportRouter();
                    JConnectionConfiguration* cc1=new JConnectionConfiguration();
                    JServer* server1=new JServer(localEndPoint1,router1,cc1);

                    //exporting object

                    JOutlook *outlook = new JOutlook();
                    JList *interfaces = new JArrayList();
                    interfaces->add(JIOutlook::getClazz());
                    server1->getIRegistry()->bind(JIOutlook::getClazz()->getName(), outlook, interfaces);

                    synchronized(this,{
                        wait();
                    })

                    //this->wait();

                }catch(JThrowable* th){
                    th->printStackTrace();
                    throw th;
                }
            }

            JOutlookTest::~JOutlookTest(){
            }
        }
    }
}
