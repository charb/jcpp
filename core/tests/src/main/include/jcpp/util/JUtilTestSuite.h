#ifndef JCPP_UTIL_TEST_SUITE_H
#define JCPP_UTIL_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace util{

	    //@Class(canonicalName="jcpp.util.UtilTestSuite", simpleName="UtilTestSuite");
	    class JCPP_EXPORT JUtilTestSuite : public JTestSuite{
	    public:
	        JUtilTestSuite();

	        static JClass* getClazz();

	        virtual ~JUtilTestSuite();
	    };
	}
}
#endif
