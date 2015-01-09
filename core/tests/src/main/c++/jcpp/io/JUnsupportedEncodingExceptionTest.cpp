#include "jcpp/io/JUnsupportedEncodingExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JUnsupportedEncodingException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JUnsupportedEncodingExceptionTest::JUnsupportedEncodingExceptionTest():JSerializableTest(getClazz()){
        }

        void JUnsupportedEncodingExceptionTest::equals(JObject* reached, JObject* expected){
            JUnsupportedEncodingException* r=dynamic_cast<JUnsupportedEncodingException*>(reached);
            r->printStackTrace();
            JUnsupportedEncodingException* e=dynamic_cast<JUnsupportedEncodingException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUnsupportedEncodingExceptionTest::getSerializableObject(){
            JUnsupportedEncodingException* cause=new JUnsupportedEncodingException(new JString("This is the cause"));
            JUnsupportedEncodingException* exception=new JUnsupportedEncodingException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JUnsupportedEncodingExceptionTest::~JUnsupportedEncodingExceptionTest(){
        }
    }
}
