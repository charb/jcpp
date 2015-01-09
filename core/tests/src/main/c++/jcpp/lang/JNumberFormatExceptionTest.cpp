#include "jcpp/lang/JNumberFormatExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNumberFormatException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNumberFormatExceptionTest::JNumberFormatExceptionTest():JSerializableTest(getClazz()){
        }

        void JNumberFormatExceptionTest::equals(JObject* reached, JObject* expected){
            JNumberFormatException* r=dynamic_cast<JNumberFormatException*>(reached);
            r->printStackTrace();
            JNumberFormatException* e=dynamic_cast<JNumberFormatException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNumberFormatExceptionTest::getSerializableObject(){
            JNumberFormatException* cause=new JNumberFormatException(new JString("This is the cause"));            
            JNumberFormatException* exception=new JNumberFormatException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNumberFormatExceptionTest::~JNumberFormatExceptionTest(){
        }
    }
}
