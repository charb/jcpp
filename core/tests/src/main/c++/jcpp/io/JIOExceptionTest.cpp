#include "jcpp/io/JIOExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JIOException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JIOExceptionTest::JIOExceptionTest():JSerializableTest(getClazz()){
        }

        void JIOExceptionTest::equals(JObject* reached, JObject* expected){
            JIOException* r=dynamic_cast<JIOException*>(reached);
            r->printStackTrace();
            JIOException* e=dynamic_cast<JIOException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIOExceptionTest::getSerializableObject(){
            JIOException* cause=new JIOException(new JString("This is the cause"));
            JIOException* exception=new JIOException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIOExceptionTest::~JIOExceptionTest(){
        }
    }
}
