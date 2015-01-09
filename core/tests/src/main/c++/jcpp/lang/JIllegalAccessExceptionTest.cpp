#include "jcpp/lang/JIllegalAccessExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalAccessException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalAccessExceptionTest::JIllegalAccessExceptionTest():JSerializableTest(getClazz()){
        }

        void JIllegalAccessExceptionTest::equals(JObject* reached, JObject* expected){
            JIllegalAccessException* r=dynamic_cast<JIllegalAccessException*>(reached);
            r->printStackTrace();
            JIllegalAccessException* e=dynamic_cast<JIllegalAccessException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIllegalAccessExceptionTest::getSerializableObject(){
            JIllegalAccessException* cause=new JIllegalAccessException(new JString("This is the cause"));            
            JIllegalAccessException* exception=new JIllegalAccessException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIllegalAccessExceptionTest::~JIllegalAccessExceptionTest(){
        }
    }
}
