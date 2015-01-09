#include "jcpp/io/JInvalidClassExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JInvalidClassException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JInvalidClassExceptionTest::JInvalidClassExceptionTest():JSerializableTest(getClazz()){
        }

        void JInvalidClassExceptionTest::equals(JObject* reached, JObject* expected){
            JInvalidClassException* r=dynamic_cast<JInvalidClassException*>(reached);
            r->printStackTrace();
            JInvalidClassException* e=dynamic_cast<JInvalidClassException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getClassname(),e->getClassname());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInvalidClassExceptionTest::getSerializableObject(){
            JInvalidClassException* cause=new JInvalidClassException(new JString("SAMPLE"),new JString("This is the cause"));
            JInvalidClassException* exception=new JInvalidClassException(new JString("SAMPLE"),new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JInvalidClassExceptionTest::~JInvalidClassExceptionTest(){
        }
    }
}
