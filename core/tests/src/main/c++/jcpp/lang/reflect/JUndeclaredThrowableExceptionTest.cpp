#include "jcpp/lang/reflect/JUndeclaredThrowableExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JUndeclaredThrowableException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
    	namespace reflect{
        JUndeclaredThrowableExceptionTest::JUndeclaredThrowableExceptionTest():JSerializableTest(getClazz()){
        }

        void JUndeclaredThrowableExceptionTest::equals(JObject* reached, JObject* expected){
            JUndeclaredThrowableException* r=dynamic_cast<JUndeclaredThrowableException*>(reached);
            r->printStackTrace();
            JUndeclaredThrowableException* e=dynamic_cast<JUndeclaredThrowableException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getUndeclaredThrowable()->getMessage(),e->getUndeclaredThrowable()->getMessage());
        }

        JObject* JUndeclaredThrowableExceptionTest::getSerializableObject(){
            JUndeclaredThrowableException* cause=new JUndeclaredThrowableException(null,new JString("This is the cause"));
            JUndeclaredThrowableException* exception=new JUndeclaredThrowableException(cause,new JString("The exception to test"));
            return exception;
        }

        JUndeclaredThrowableExceptionTest::~JUndeclaredThrowableExceptionTest(){
        }
    }
    }
}
