#include "jcpp/io/JUncheckedIOExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JUncheckedIOException.h"
#include "jcpp/io/JIOException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JUncheckedIOExceptionTest::JUncheckedIOExceptionTest():JSerializableTest(getClazz()){
        }

        void JUncheckedIOExceptionTest::equals(JObject* reached, JObject* expected){
            JUncheckedIOException* r=dynamic_cast<JUncheckedIOException*>(reached);
            r->printStackTrace();
            JUncheckedIOException* e=dynamic_cast<JUncheckedIOException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUncheckedIOExceptionTest::getSerializableObject(){
            JIOException* cause=new JIOException(new JString("This is the cause"));
            JUncheckedIOException* exception=new JUncheckedIOException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JUncheckedIOExceptionTest::~JUncheckedIOExceptionTest(){
        }
    }
}
