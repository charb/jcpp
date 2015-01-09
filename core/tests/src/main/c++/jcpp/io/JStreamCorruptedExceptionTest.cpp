#include "jcpp/io/JStreamCorruptedExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JStreamCorruptedException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JStreamCorruptedExceptionTest::JStreamCorruptedExceptionTest():JSerializableTest(getClazz()){
        }

        void JStreamCorruptedExceptionTest::equals(JObject* reached, JObject* expected){
            JStreamCorruptedException* r=dynamic_cast<JStreamCorruptedException*>(reached);
            r->printStackTrace();
            JStreamCorruptedException* e=dynamic_cast<JStreamCorruptedException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JStreamCorruptedExceptionTest::getSerializableObject(){
            JStreamCorruptedException* cause=new JStreamCorruptedException(new JString("This is the cause"));
            JStreamCorruptedException* exception=new JStreamCorruptedException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JStreamCorruptedExceptionTest::~JStreamCorruptedExceptionTest(){
        }
    }
}
