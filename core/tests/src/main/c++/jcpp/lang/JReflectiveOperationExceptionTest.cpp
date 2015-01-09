#include "jcpp/lang/JReflectiveOperationExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JReflectiveOperationException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JReflectiveOperationExceptionTest::JReflectiveOperationExceptionTest():JSerializableTest(getClazz()){
        }

        void JReflectiveOperationExceptionTest::equals(JObject* reached, JObject* expected){
            JReflectiveOperationException* r=dynamic_cast<JReflectiveOperationException*>(reached);
            r->printStackTrace();
            JReflectiveOperationException* e=dynamic_cast<JReflectiveOperationException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JReflectiveOperationExceptionTest::getSerializableObject(){
            JReflectiveOperationException* cause=new JReflectiveOperationException(new JString("This is the cause"));            
            JReflectiveOperationException* exception=new JReflectiveOperationException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JReflectiveOperationExceptionTest::~JReflectiveOperationExceptionTest(){
        }
    }
}
