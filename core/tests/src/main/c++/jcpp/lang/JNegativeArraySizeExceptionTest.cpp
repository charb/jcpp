#include "jcpp/lang/JNegativeArraySizeExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNegativeArraySizeException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNegativeArraySizeExceptionTest::JNegativeArraySizeExceptionTest():JSerializableTest(getClazz()){
        }

        void JNegativeArraySizeExceptionTest::equals(JObject* reached, JObject* expected){
            JNegativeArraySizeException* r=dynamic_cast<JNegativeArraySizeException*>(reached);
            r->printStackTrace();
            JNegativeArraySizeException* e=dynamic_cast<JNegativeArraySizeException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNegativeArraySizeExceptionTest::getSerializableObject(){
            JNegativeArraySizeException* cause=new JNegativeArraySizeException(new JString("This is the cause"));            
            JNegativeArraySizeException* exception=new JNegativeArraySizeException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNegativeArraySizeExceptionTest::~JNegativeArraySizeExceptionTest(){
        }
    }
}
