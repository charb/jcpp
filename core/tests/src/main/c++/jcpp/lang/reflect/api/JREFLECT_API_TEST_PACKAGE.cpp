#include "jcpp/lang/reflect/api/JREFLECT_API_TEST_PACKAGE.h"
#include "jcpp/lang/reflect/JREFLECT_TEST_PACKAGE.h"
#include "jcpp/lang/reflect/api/JReflectAPITestSuite.h"
#include "jcpp/lang/reflect/api/JGetClassAPITest.h"
#include "jcpp/lang/reflect/api/JClassAPITest.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{
        	namespace api {
				JREFLECT_API_TEST_PACKAGE::JREFLECT_API_TEST_PACKAGE():JPackage(new JString("java.lang.reflect.api"),JPackage::getClazz()){
					addClass(JReflectAPITestSuite::getClazz());
					addClass(JClassAPITest::getClazz());
					addClass(JGetClassAPITest::getClazz());
				}

				JPackage* JREFLECT_API_TEST_PACKAGE::getSuperPackage(){
					return jcpp::lang::reflect::JREFLECT_TEST_PACKAGE::getPackage();
				}

				JList* JREFLECT_API_TEST_PACKAGE::getPackages(){
					return packages;
				}

				static JREFLECT_API_TEST_PACKAGE* pk=null;

				JREFLECT_API_TEST_PACKAGE* JREFLECT_API_TEST_PACKAGE::getPackage(){
					if (pk==null){
						pk=new JREFLECT_API_TEST_PACKAGE();
					}
					return pk;
				}

				JREFLECT_API_TEST_PACKAGE::~JREFLECT_API_TEST_PACKAGE(){
				}
			}
		}
    }
}
