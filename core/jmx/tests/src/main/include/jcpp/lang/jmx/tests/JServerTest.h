/*
 * ServerTest.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mmaarouf
 */

#ifndef SERVERTEST_H_
#define SERVERTEST_H_


#include "junit/framework/JTestCase.h"

using namespace junit::framework;

namespace jcpp{
	namespace lang{
		class JClass;
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

			// @Class(canonicalName="jcpp.lang.jmx.tests.ServerTest", simpleName="ServerTest");
				class JCPP_EXPORT JServerTest: public JTestCase{
				public:
					JServerTest();

					virtual void test();

					static JClass* getClazz();
					virtual ~JServerTest();
				};
			}
		}
	}
}



#endif /* SERVERTEST_H_ */
