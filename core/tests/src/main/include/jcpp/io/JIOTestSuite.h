#ifndef JCPP_IO_TEST_SUITE_H
#define JCPP_IO_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace io{
	   	//@Class(canonicalName="jcpp.io.IOTestSuite", simpleName="IOTestSuite");
	    class JCPP_EXPORT JIOTestSuite : public JTestSuite{
	    public:
	        JIOTestSuite();

	        static JClass* getClazz();

	        virtual ~JIOTestSuite();
	    };
	}
}
#endif
