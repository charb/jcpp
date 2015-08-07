#include "jcpp/lang/jmx/tests/JRemoteServerTest.h"


#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/rmi/server/transport/JTransportRouter.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"


#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JSystem.h"

#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/JMBeanServerFactory.h"
#include "jcpp/lang/jmx/JMBeanServerConnection.h"
#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"

#include "jcpp/lang/jmx/tests/JHello.h"
#include "jcpp/lang/jmx/tests/JHelloMBean.h"



using namespace jcpp::net;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::gateway;
using namespace jcpp::rmi::server::connection;
using namespace jcpp::rmi::server::transport;
using namespace jcpp::io;
using namespace junit::framework;
using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{
				JRemoteServerTest::JRemoteServerTest():JTestCase(getClazz(), new JString("test")){
				}

				void JRemoteServerTest::test(){
					try{
						JAddress* adr = new JAddress();
						adr->setHostName(JInetAddress::getLocalHost()->getHostName());
						adr->setPort(9800);
						JEndPoint* localEndPoint1=new JEndPoint(adr,new JString("site1"));

						 //initializing server
						JTransportRouter* router1=new JTransportRouter();
						JConnectionConfiguration* cc1=new JConnectionConfiguration();
						JServer* server1=new JServer(localEndPoint1,router1,cc1);


						JMBeanServer* mbeanServer = JMBeanServerFactory::createJMBeanServer();
						JString* mbeanName = new JString("jcpp.lang.jmx.tests:type=Hello");
						JHello* mbean = new JHello();
						mbeanServer->registerMBean(mbean, mbeanName);


						JList* interfaces = new JArrayList();
						interfaces->add(JMBeanServerConnection::getClazz());
						server1->getIRegistry()->bind(JMBeanServer::getClazz()->getName(), dynamic_cast<JObject*>(mbeanServer), interfaces);


						JSystem::out->println(new JString("<---------- Waiting ------------->"));
						synchronized(this,{
							wait();
						})



					} catch(JThrowable* th){
	                    th->printStackTrace();
	                    throw th;
	                }
				}


				JRemoteServerTest::~JRemoteServerTest(){
				}

			}
		}
	}
}
