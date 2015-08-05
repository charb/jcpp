/*
 * JServerTestSuite.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mmaarouf
 */

#ifndef JSERVERTESTSUITE_H_
#define JSERVERTESTSUITE_H_

#include "junit/framework/JTestSuite.h"

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
			// @Class(canonicalName="jcpp.lang.jmx.tests.ServerTestSuite", simpleName="ServerTestSuite");
				class JCPP_EXPORT JServerTestSuite: public JTestSuite{
				public:
					JServerTestSuite();

					static JServerTestSuite* suite();

					static JClass* getClazz();

					virtual ~JServerTestSuite();
				};
			}
		}
	}
}



#endif /* JSERVERTESTSUITE_H_ */
