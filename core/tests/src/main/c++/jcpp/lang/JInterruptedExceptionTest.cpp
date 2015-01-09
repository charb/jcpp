#include "jcpp/lang/JInterruptedExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JInterruptedException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInterruptedExceptionTest::JInterruptedExceptionTest():JSerializableTest(getClazz()){
        }

        void JInterruptedExceptionTest::equals(JObject* reached, JObject* expected){
            JInterruptedException* r=dynamic_cast<JInterruptedException*>(reached);
            r->printStackTrace();
            JInterruptedException* e=dynamic_cast<JInterruptedException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInterruptedExceptionTest::getSerializableObject(){
            JInterruptedException* cause=new JInterruptedException(new JString("This is the cause"));            
            JInterruptedException* exception=new JInterruptedException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JInterruptedExceptionTest::~JInterruptedExceptionTest(){
        }
    }
}
