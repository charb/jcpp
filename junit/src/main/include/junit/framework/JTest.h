#ifndef JUNIT_FRAMEWORK_JTEST_H
#define JUNIT_FRAMEWORK_JTEST_H

#include "jcpp/lang/JInterface.h"
#include "junit/framework/JTestResult.h"

using namespace jcpp::lang;

namespace junit{
    namespace framework{
    	// @Class(canonicalName="junit.framework.Test", simpleName="Test");
        class JCPP_EXPORT JTest : public JInterface{
            public:
                static JClass* getClazz();

                virtual jint countTestCases()=0;

                virtual void run(JTestResult* reult)=0;

                virtual ~JTest();
        };
    }
}
#endif
