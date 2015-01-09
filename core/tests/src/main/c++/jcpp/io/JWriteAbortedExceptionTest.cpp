#include "jcpp/io/JWriteAbortedExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JWriteAbortedException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JWriteAbortedExceptionTest::JWriteAbortedExceptionTest():JSerializableTest(getClazz()){
        }

        void JWriteAbortedExceptionTest::equals(JObject* reached, JObject* expected){
            JWriteAbortedException* r=dynamic_cast<JWriteAbortedException*>(reached);
            r->printStackTrace();
            JWriteAbortedException* e=dynamic_cast<JWriteAbortedException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JWriteAbortedExceptionTest::getSerializableObject(){
            JWriteAbortedException* cause=new JWriteAbortedException(new JString("This is the cause"),null);
            JWriteAbortedException* exception=new JWriteAbortedException(new JString("The exception to test"),cause);
            return exception;
        }

        JWriteAbortedExceptionTest::~JWriteAbortedExceptionTest(){
        }
    }
}
