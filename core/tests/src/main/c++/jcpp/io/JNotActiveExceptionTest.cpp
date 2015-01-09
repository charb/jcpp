#include "jcpp/io/JNotActiveExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JNotActiveException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JNotActiveExceptionTest::JNotActiveExceptionTest():JSerializableTest(getClazz()){
        }

        void JNotActiveExceptionTest::equals(JObject* reached, JObject* expected){
            JNotActiveException* r=dynamic_cast<JNotActiveException*>(reached);
            r->printStackTrace();
            JNotActiveException* e=dynamic_cast<JNotActiveException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNotActiveExceptionTest::getSerializableObject(){
            JNotActiveException* cause=new JNotActiveException(new JString("This is the cause"));
            JNotActiveException* exception=new JNotActiveException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNotActiveExceptionTest::~JNotActiveExceptionTest(){
        }
    }
}
