/*
 * JRemoteServerTest.h
 *
 *  Created on: Aug 7, 2015
 *      Author: mmaarouf
 */

#ifndef JREMOTESERVERTEST_H_
#define JREMOTESERVERTEST_H_



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

			// @Class(canonicalName="jcpp.lang.jmx.tests.RemoteServerTest", simpleName="RemoteServerTest");
				class JCPP_EXPORT JRemoteServerTest: public JTestCase{
				public:
					JRemoteServerTest();

					virtual void test();

					static JClass* getClazz();
					virtual ~JRemoteServerTest();
				};
			}
		}
	}
}




#endif /* JREMOTESERVERTEST_H_ */
