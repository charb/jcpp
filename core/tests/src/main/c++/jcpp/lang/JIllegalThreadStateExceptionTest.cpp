#include "jcpp/lang/JIllegalThreadStateExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalThreadStateException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalThreadStateExceptionTest::JIllegalThreadStateExceptionTest():JSerializableTest(getClazz()){
        }

        void JIllegalThreadStateExceptionTest::equals(JObject* reached, JObject* expected){
            JIllegalThreadStateException* r=dynamic_cast<JIllegalThreadStateException*>(reached);
            r->printStackTrace();
            JIllegalThreadStateException* e=dynamic_cast<JIllegalThreadStateException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIllegalThreadStateExceptionTest::getSerializableObject(){
            JIllegalThreadStateException* cause=new JIllegalThreadStateException(new JString("This is the cause"));            
            JIllegalThreadStateException* exception=new JIllegalThreadStateException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIllegalThreadStateExceptionTest::~JIllegalThreadStateExceptionTest(){
        }
    }
}
