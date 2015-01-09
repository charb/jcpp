#ifndef JCPP_LANG_REFLECT_API_TEST_SUITE_H
#define JCPP_LANG_REFLECT_API_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace lang{
		namespace reflect{
			namespace api {
			    //@Class(canonicalName="jcpp.lang.reflect.api.ReflectAPITestSuite", simpleName="ReflectAPITestSuite");
				class JCPP_EXPORT JReflectAPITestSuite : public JTestSuite{
				public:
					JReflectAPITestSuite();

					static JClass* getClazz();

					virtual ~JReflectAPITestSuite();
				};
			}
		}
	}
}
#endif
