#ifndef JUNIT_FRAMEWORK_JASSERTION_FAILED_ERROR_H
#define JUNIT_FRAMEWORK_JASSERTION_FAILED_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JAssertionError.h"

using namespace jcpp::lang;

namespace junit{
    namespace framework{
		// @Class(canonicalName="junit.framework.AssertionFailedError", simpleName="AssertionFailedError");
        class JCPP_EXPORT JAssertionFailedError : public JAssertionError{
        	private:
        		static const jlong serialVersionUID = 1LL;

        	protected:
        		JAssertionFailedError(JClass* _class);

            public:
                static JClass* getClazz();

                JAssertionFailedError();

                JAssertionFailedError(JString* message);

                virtual ~JAssertionFailedError();
        };
    }
}
#endif
