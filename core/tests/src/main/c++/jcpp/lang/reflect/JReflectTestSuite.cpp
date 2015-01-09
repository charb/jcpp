#include "jcpp/lang/reflect/JReflectTestSuite.h"
#include "jcpp/lang/reflect/api/JReflectAPITestSuite.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JInvocationTargetExceptionTest.h"
#include "jcpp/lang/reflect/JMalformedParameterizedTypeExceptionTest.h"
#include "jcpp/lang/reflect/JMalformedParametersExceptionTest.h"
#include "jcpp/lang/reflect/JUndeclaredThrowableExceptionTest.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace reflect{


            JReflectTestSuite::JReflectTestSuite():JTestSuite(JReflectTestSuite::getClazz(),true){
                addTest(new JInvocationTargetExceptionTest());
                addTest(new JMalformedParameterizedTypeExceptionTest());
                //addTest(new JMalformedParametersExceptionTest()); 		//TODO reactivate when on java8
                addTest(new JUndeclaredThrowableExceptionTest());
                addTest(new api::JReflectAPITestSuite());
            }

            JReflectTestSuite::~JReflectTestSuite(){
            }
        }
    }
}
