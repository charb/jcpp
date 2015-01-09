#include "jcpp/lang/JUnsupportedOperationExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JUnsupportedOperationException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnsupportedOperationExceptionTest::JUnsupportedOperationExceptionTest():JSerializableTest(getClazz()){
        }

        void JUnsupportedOperationExceptionTest::equals(JObject* reached, JObject* expected){
            JUnsupportedOperationException* r=dynamic_cast<JUnsupportedOperationException*>(reached);
            r->printStackTrace();
            JUnsupportedOperationException* e=dynamic_cast<JUnsupportedOperationException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUnsupportedOperationExceptionTest::getSerializableObject(){
            JUnsupportedOperationException* cause=new JUnsupportedOperationException(new JString("This is the cause"));
            JUnsupportedOperationException* ex=new JUnsupportedOperationException(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JUnsupportedOperationExceptionTest::~JUnsupportedOperationExceptionTest(){
        }
    }
}
