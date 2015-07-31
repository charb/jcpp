#ifndef JCPP_LANG_INFO_JMYTEST_H_
#define JCPP_LANG_INFO_JMYTEST_H_

#include "junit/framework/JTestCase.h"

using namespace junit::framework;
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace info{
        	//@Class(canonicalName="jcpp.lang.info.JMyTest", simpleName="JMyTest");
        	class JCPP_EXPORT JMyTest : public JTestCase{
        	public:
        		JMyTest();

        		static JClass *getClazz();

        		virtual void test();

        		virtual ~JMyTest();
        	};
        }
    }
}


#endif
