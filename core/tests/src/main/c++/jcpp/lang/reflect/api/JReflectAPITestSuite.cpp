#include "jcpp/lang/reflect/api/JReflectAPITestSuite.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/api/JGetClassAPITest.h"
#include "jcpp/lang/reflect/api/JClassAPITest.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{
        	namespace api {

				JReflectAPITestSuite::JReflectAPITestSuite():JTestSuite(JReflectAPITestSuite::getClazz(),true){
					//addTest(new JClassAPITest());
					//addTest(new JGetClassAPITest());
				}

				JReflectAPITestSuite::~JReflectAPITestSuite(){
				}
			}
		}
    }
}
