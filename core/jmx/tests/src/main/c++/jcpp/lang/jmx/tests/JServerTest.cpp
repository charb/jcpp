#include "jcpp/lang/jmx/tests/JServerTest.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"
//#include "jcpp/lang/jmx/JMBeanServer.h"
//#include "jcpp/lang/jmx/JMBeanServerFactory.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

				JServerTest::JServerTest():JTestCase(getClazz(), new JString("test")){
				}

				void JServerTest::test(){
					try{
						JSystem::out->println("<------------ RUNNING SERVER TEST --------------------->");

//						JMBeanServer* mbs = JMBeanServerFactory::createJMBeanServer();
					} catch(JThrowable* th){
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
