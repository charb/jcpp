#include "jcpp/lang/JNoSuchMethodExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoSuchMethodException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchMethodExceptionTest::JNoSuchMethodExceptionTest():JSerializableTest(getClazz()){
        }

        void JNoSuchMethodExceptionTest::equals(JObject* reached, JObject* expected){
            JNoSuchMethodException* r=dynamic_cast<JNoSuchMethodException*>(reached);
            r->printStackTrace();
            JNoSuchMethodException* e=dynamic_cast<JNoSuchMethodException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNoSuchMethodExceptionTest::getSerializableObject(){
            JNoSuchMethodException* cause=new JNoSuchMethodException(new JString("This is the cause"));            
            JNoSuchMethodException* exception=new JNoSuchMethodException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNoSuchMethodExceptionTest::~JNoSuchMethodExceptionTest(){
        }
    }
}
