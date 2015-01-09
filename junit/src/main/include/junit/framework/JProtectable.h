#ifndef JUNIT_FRAMEWORK_JPROTECTABLE_H
#define JUNIT_FRAMEWORK_JPROTECTABLE_H

#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace junit{
    namespace framework{
    	// @Class(canonicalName="junit.framework.Protectable", simpleName="Protectable");
        class JCPP_EXPORT JProtectable : public JInterface{
            public:
                static JClass* getClazz();

                virtual void protect()=0;

                virtual ~JProtectable();
        };
    }
}
#endif
