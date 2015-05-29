#include "jcpp/lang/info/JInfoTestSuite.h"

#include "jcpp/lang/info/JObjectInfoGroupVisitorResultTest.h"
#include "jcpp/lang/info/JMethodCallVisitorResultTest.h"
#include "jcpp/lang/info/JClassInfoVisitorResultTest.h"

using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace lang {
		namespace info {
			JInfoTestSuite::JInfoTestSuite() :
					JTestSuite(JInfoTestSuite::getClazz(), true){
				addTest(new JObjectInfoGroupVisitorResultTest());
				addTest(new JMethodCallVisitorResultTest());
				addTest(new JClassInfoVisitorResultTest());
			}

			JInfoTestSuite::~JInfoTestSuite(){
			}
		}
	}
}

