#include "jcpp/io/JInvalidObjectExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JInvalidObjectException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{


        JInvalidObjectExceptionTest::JInvalidObjectExceptionTest():JSerializableTest(getClazz()){
        }

        void JInvalidObjectExceptionTest::equals(JObject* reached, JObject* expected){
            JInvalidObjectException* r=dynamic_cast<JInvalidObjectException*>(reached);
            r->printStackTrace();
            JInvalidObjectException* e=dynamic_cast<JInvalidObjectException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInvalidObjectExceptionTest::getSerializableObject(){
            JInvalidObjectException* cause=new JInvalidObjectException(new JString("This is the cause"));
            JInvalidObjectException* exception=new JInvalidObjectException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JInvalidObjectExceptionTest::~JInvalidObjectExceptionTest(){
        }
    }
}
