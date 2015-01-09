#ifndef JUNIT_FRAMEWORK_JCOMPARISON_FAILURE_H
#define JUNIT_FRAMEWORK_JCOMPARISON_FAILURE_H

#include "junit/framework/JAssertionFailedError.h"

using namespace jcpp::lang;

namespace junit{
    namespace framework{
		// @Class(canonicalName="junit.framework.ComparisonFailure", simpleName="ComparisonFailure");
        class JCPP_EXPORT JComparisonFailure : public JAssertionFailedError{
        	private:
        		static const jlong serialVersionUID = 1LL;

        	protected:
        		JString* fExpected;
    			JString* fActual;

                JComparisonFailure();


            public:
                JComparisonFailure(JString* message, JString* expected, JString* actual);

                static JClass* getClazz();

                virtual JString* getActual();

				virtual JString* getExpected();

                virtual ~JComparisonFailure();
        };
    }
}
#endif
