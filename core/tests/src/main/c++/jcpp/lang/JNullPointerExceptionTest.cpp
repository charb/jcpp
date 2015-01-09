#include "jcpp/lang/JNullPointerExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNullPointerException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNullPointerExceptionTest::JNullPointerExceptionTest():JSerializableTest(getClazz()){
        }

        void JNullPointerExceptionTest::equals(JObject* reached, JObject* expected){
            JNullPointerException* r=dynamic_cast<JNullPointerException*>(reached);
            r->printStackTrace();
            JNullPointerException* e=dynamic_cast<JNullPointerException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNullPointerExceptionTest::getSerializableObject(){
            JNullPointerException* cause=new JNullPointerException(new JString("This is the cause"));            
            JNullPointerException* exception=new JNullPointerException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNullPointerExceptionTest::~JNullPointerExceptionTest(){
        }
    }
}
