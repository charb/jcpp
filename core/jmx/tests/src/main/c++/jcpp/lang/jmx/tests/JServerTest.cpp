#include "jcpp/lang/jmx/tests/JServerTest.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/JMBeanServerFactory.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/tests/JHello.h"
#include "jcpp/lang/jmx/tests/JCopyOfHello.h"
#include "jcpp/lang/jmx/JAttribute.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/jmx/tests/innertest/JHell.h"

using namespace jcpp::lang::jmx::tests::innertest;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

				JServerTest::JServerTest():JTestCase(getClazz(), new JString("test")){
				}

				void JServerTest::test(){
					try{

						// Creating MBean Server
						JMBeanServer* mbs = JMBeanServerFactory::createJMBeanServer();

						// Creating MBean and registering it in the mbean server
						JObjectName* mbeanName = new JObjectName(new JString("jcpp.lang.jmx.tests:type=Hello"));
						JHello* mbean = new JHello();
						mbs->registerMBean(mbean, mbeanName);



						// invokding, getting, and setting attributes
						JObject* obj = mbs->invoke(mbeanName, new JString("sayHello"), null, null);

						JString* helloName = dynamic_cast<JString*>(mbs->getAttribute(mbeanName, new JString("Name")));
						JSystem::out->println(helloName);

						JAttribute* cacheSizeAttribute = new JAttribute(new JString("CacheSize"), new JInteger(234));
						mbs->setAttribute(mbeanName, cacheSizeAttribute);


						JPrimitiveObjectArray* params = new JPrimitiveObjectArray(JInteger::getClazz(), 2);
						params->set(0, new JInteger(1));
						params->set(1, new JInteger(2));

						JPrimitiveObjectArray* sig = new JPrimitiveObjectArray(JString::getClazz(), 2);
						sig->set(0, JInteger::getClazz()->getName());
						sig->set(1, JInteger::getClazz()->getName());

						JInteger* addResult = dynamic_cast<JInteger*>(mbs->invoke(mbeanName, new JString("add"), params, sig));
						JSystem::out->println(new JString("add() returned"));
						JSystem::out->println(addResult->toString());

						//----------------------------------------------------------------
						// creating and registering another mbean in the same package
						//----------------------------------------------------------------

						JSystem::out->println(new JString("\n\n\n\n"));

						JObjectName* mbeanName2 = new JObjectName(new JString("jcpp.lang.jmx.tests:type=CopyOfHello"));
						JCopyOfHello* mbean2 = new JCopyOfHello();
						mbs->registerMBean(mbean2, mbeanName2);


						// invokding, getting, and setting attributes
						JObject* obj2 = mbs->invoke(mbeanName2, new JString("sayHello"), null, null);

						JString* helloName2 = dynamic_cast<JString*>(mbs->getAttribute(mbeanName2, new JString("Name")));
						JSystem::out->println(helloName2);

						JAttribute* cacheSizeAttribute2 = new JAttribute(new JString("CacheSize"), new JInteger(234));
						mbs->setAttribute(mbeanName2, cacheSizeAttribute2);


						JPrimitiveObjectArray* params2 = new JPrimitiveObjectArray(JInteger::getClazz(), 2);
						params2->set(0, new JInteger(100));
						params2->set(1, new JInteger(200));

						JPrimitiveObjectArray* sig2 = new JPrimitiveObjectArray(JString::getClazz(), 2);
						sig2->set(0, JInteger::getClazz()->getName());
						sig2->set(1, JInteger::getClazz()->getName());

						JInteger* addResult2 = dynamic_cast<JInteger*>(mbs->invoke(mbeanName2, new JString("add"), params2, sig2));
						JSystem::out->println(new JString("add() returned"));
						JSystem::out->println(addResult2->toString());


						//-----------------------------------------------------------------
						// creating and registering another mbean in a different package
						//-----------------------------------------------------------------
//
						JSystem::out->println(new JString("\n\n\n\n"));

						JObjectName* mbeanName3 = new JObjectName(new JString("jcpp.lang.jmx.tests.innertest:type=Hell"));
						JHell* mbean3 = new JHell();
						mbs->registerMBean(mbean3, mbeanName3);



						// invokding, getting, and setting attributes
						JObject* obj3 = mbs->invoke(mbeanName3, new JString("sayHello"), null, null);

						JString* helloName3 = dynamic_cast<JString*>(mbs->getAttribute(mbeanName3, new JString("Name")));
						JSystem::out->println(helloName2);

						JAttribute* cacheSizeAttribute3 = new JAttribute(new JString("CacheSize"), new JInteger(3333));
						mbs->setAttribute(mbeanName3, cacheSizeAttribute3);


						JPrimitiveObjectArray* params3 = new JPrimitiveObjectArray(JInteger::getClazz(), 2);
						params3->set(0, new JInteger(100));
						params3->set(1, new JInteger(200));

						JPrimitiveObjectArray* sig3 = new JPrimitiveObjectArray(JString::getClazz(), 2);
						sig3->set(0, JInteger::getClazz()->getName());
						sig3->set(1, JInteger::getClazz()->getName());

						JInteger* addResult3 = dynamic_cast<JInteger*>(mbs->invoke(mbeanName3, new JString("add"), params3, sig3));
						JSystem::out->println(new JString("add() returned"));
						JSystem::out->println(addResult3->toString());


					} catch(JThrowable* th){
						JSystem::out->println(new JString("\n<------------ Exception in registerMBean --------------------->"));
						th->printStackTrace();
						throw th;
					}
				}

				JServerTest::~JServerTest(){
				}
			}
		}
	}
}
