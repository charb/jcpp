#include "jcpp/lang/jmx/tests/JServerTestSuite.h"
//#include "jcpp/lang/jmx/tests/JServerTest.h"
#include "jcpp/lang/jmx/tests/JRemoteServerTest.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

				JServerTestSuite::JServerTestSuite(): JTestSuite(JServerTestSuite::getClazz(), true){
					addTest(new JRemoteServerTest());
//					addTest(new JServerTest());
				}

				JServerTestSuite* JServerTestSuite::suite(){
					return new JServerTestSuite();
				}

				JServerTestSuite::~JServerTestSuite(){
				}
			}
		}
	}
}
