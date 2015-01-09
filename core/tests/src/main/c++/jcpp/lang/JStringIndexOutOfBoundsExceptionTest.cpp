#include "jcpp/lang/JStringIndexOutOfBoundsExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringIndexOutOfBoundsException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStringIndexOutOfBoundsExceptionTest::JStringIndexOutOfBoundsExceptionTest():JSerializableTest(getClazz()){
        }

        void JStringIndexOutOfBoundsExceptionTest::equals(JObject* reached, JObject* expected){
            JStringIndexOutOfBoundsException* r=dynamic_cast<JStringIndexOutOfBoundsException*>(reached);
            r->printStackTrace();
            JStringIndexOutOfBoundsException* e=dynamic_cast<JStringIndexOutOfBoundsException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JStringIndexOutOfBoundsExceptionTest::getSerializableObject(){
            JStringIndexOutOfBoundsException* cause=new JStringIndexOutOfBoundsException(new JString("This is the cause"));            
            JStringIndexOutOfBoundsException* exception=new JStringIndexOutOfBoundsException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JStringIndexOutOfBoundsExceptionTest::~JStringIndexOutOfBoundsExceptionTest(){
        }
    }
}
