#include "jcpp/io/JNotSerializableExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JNotSerializableException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JNotSerializableExceptionTest::JNotSerializableExceptionTest():JSerializableTest(getClazz()){
        }

        void JNotSerializableExceptionTest::equals(JObject* reached, JObject* expected){
            JNotSerializableException* r=dynamic_cast<JNotSerializableException*>(reached);
            r->printStackTrace();
            JNotSerializableException* e=dynamic_cast<JNotSerializableException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNotSerializableExceptionTest::getSerializableObject(){
            JNotSerializableException* cause=new JNotSerializableException(new JString("This is the cause"));
            JNotSerializableException* exception=new JNotSerializableException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNotSerializableExceptionTest::~JNotSerializableExceptionTest(){
        }
    }
}
