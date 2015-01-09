#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_TEST_SUITE_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace util{
		namespace concurrent{
			namespace atomic{
				// @Class(canonicalName="jcpp.util.concurrent.atomic.AtomicTestSuite", simpleName="AtomicTestSuite");
			    class JCPP_EXPORT JAtomicTestSuite : public JTestSuite{
			    public:
			        JAtomicTestSuite();

			        static JClass* getClazz();

			        virtual ~JAtomicTestSuite();
			    };
			}
		}
	}
}
#endif
