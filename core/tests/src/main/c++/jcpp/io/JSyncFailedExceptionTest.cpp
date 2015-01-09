#include "jcpp/io/JSyncFailedExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JSyncFailedException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JSyncFailedExceptionTest::JSyncFailedExceptionTest():JSerializableTest(getClazz()){
        }

        void JSyncFailedExceptionTest::equals(JObject* reached, JObject* expected){
            JSyncFailedException* r=dynamic_cast<JSyncFailedException*>(reached);
            r->printStackTrace();
            JSyncFailedException* e=dynamic_cast<JSyncFailedException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JSyncFailedExceptionTest::getSerializableObject(){
            JSyncFailedException* cause=new JSyncFailedException(new JString("This is the cause"));
            JSyncFailedException* exception=new JSyncFailedException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JSyncFailedExceptionTest::~JSyncFailedExceptionTest(){
        }
    }
}
