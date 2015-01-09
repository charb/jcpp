#include "jcpp/lang/JRuntimeExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JRuntimeExceptionTest::JRuntimeExceptionTest():JSerializableTest(getClazz()){
        }

        void JRuntimeExceptionTest::equals(JObject* reached, JObject* expected){
            JRuntimeException* r=dynamic_cast<JRuntimeException*>(reached);
            r->printStackTrace();
            JRuntimeException* e=dynamic_cast<JRuntimeException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JRuntimeExceptionTest::getSerializableObject(){
            JRuntimeException* cause=new JRuntimeException(new JString("This is the cause"));            
            JRuntimeException* exception=new JRuntimeException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JRuntimeExceptionTest::~JRuntimeExceptionTest(){
        }
    }
}
