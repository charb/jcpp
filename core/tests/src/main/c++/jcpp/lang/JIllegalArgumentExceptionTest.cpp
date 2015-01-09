#include "jcpp/lang/JIllegalArgumentExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalArgumentException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalArgumentExceptionTest::JIllegalArgumentExceptionTest():JSerializableTest(getClazz()){
        }

        void JIllegalArgumentExceptionTest::equals(JObject* reached, JObject* expected){
            JIllegalArgumentException* r=dynamic_cast<JIllegalArgumentException*>(reached);
            r->printStackTrace();
            JIllegalArgumentException* e=dynamic_cast<JIllegalArgumentException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIllegalArgumentExceptionTest::getSerializableObject(){
            JIllegalArgumentException* cause=new JIllegalArgumentException(new JString("This is the cause"));            
            JIllegalArgumentException* exception=new JIllegalArgumentException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIllegalArgumentExceptionTest::~JIllegalArgumentExceptionTest(){
        }
    }
}
