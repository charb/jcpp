#include "jcpp/lang/JArithmeticExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JArithmeticExceptionTest::JArithmeticExceptionTest():JSerializableTest(getClazz()){
        }

        void JArithmeticExceptionTest::equals(JObject* reached, JObject* expected){
            JArithmeticException* r=dynamic_cast<JArithmeticException*>(reached);
            r->printStackTrace();
            JArithmeticException* e=dynamic_cast<JArithmeticException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JArithmeticExceptionTest::getSerializableObject(){
            JArithmeticException* cause=new JArithmeticException(new JString("This is the cause"));
            JArithmeticException* exc=new JArithmeticException(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JArithmeticExceptionTest::~JArithmeticExceptionTest(){
        }
    }
}
