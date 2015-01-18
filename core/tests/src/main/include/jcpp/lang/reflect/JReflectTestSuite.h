#ifndef JCPP_LANG_REFLECT_TEST_SUITE_H
#define JCPP_LANG_REFLECT_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace lang{
		namespace reflect{
		   	//@Class(canonicalName="jcpp.lang.reflect.ReflectTestSuite", simpleName="ReflectTestSuite");
		    class JCPP_EXPORT JReflectTestSuite : public JTestSuite{
		    public:
		        JReflectTestSuite();

		        static JClass* getClazz();

		        virtual ~JReflectTestSuite();
		    };
		}
	}
}
#endif
