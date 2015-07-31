#include "jcpp/lang/info/JMyTestSuite.h"

#include "jcpp/lang/info/JMyTest.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
	namespace lang{
		namespace info{
			JMyTestSuite :: JMyTestSuite(): JTestSuite(getClazz(), true){
				addTest(new JMyTest());
			}

			JMyTestSuite::~JMyTestSuite(){
			}
		}
	}
}

