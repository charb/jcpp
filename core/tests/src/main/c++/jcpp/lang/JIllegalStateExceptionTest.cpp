#include "jcpp/lang/JIllegalStateExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalStateException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalStateExceptionTest::JIllegalStateExceptionTest():JSerializableTest(getClazz()){
        }

        void JIllegalStateExceptionTest::equals(JObject* reached, JObject* expected){
            JIllegalStateException* r=dynamic_cast<JIllegalStateException*>(reached);
            r->printStackTrace();
            JIllegalStateException* e=dynamic_cast<JIllegalStateException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIllegalStateExceptionTest::getSerializableObject(){
            JIllegalStateException* cause=new JIllegalStateException(new JString("This is the cause"));            
            JIllegalStateException* exception=new JIllegalStateException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIllegalStateExceptionTest::~JIllegalStateExceptionTest(){
        }
    }
}
