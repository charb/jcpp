#ifndef JCPP_NIO_TEST_SUITE_H
#define JCPP_NIO_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp {
	namespace nio {

		//@Class(canonicalName="jcpp.nio.NIOTestSuite", simpleName="NIOTestSuite");
		class JCPP_EXPORT JNIOTestSuite : public JTestSuite {
		public:
			JNIOTestSuite();

			static JClass* getClazz();

			virtual ~JNIOTestSuite();
		};
	}
}

#endif
