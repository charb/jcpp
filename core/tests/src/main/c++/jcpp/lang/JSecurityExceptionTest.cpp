#include "jcpp/lang/JSecurityExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JSecurityException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JSecurityExceptionTest::JSecurityExceptionTest():JSerializableTest(getClazz()){
        }

        void JSecurityExceptionTest::equals(JObject* reached, JObject* expected){
            JSecurityException* r=dynamic_cast<JSecurityException*>(reached);
            r->printStackTrace();
            JSecurityException* e=dynamic_cast<JSecurityException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JSecurityExceptionTest::getSerializableObject(){
            JSecurityException* cause=new JSecurityException(new JString("This is the cause"));            
            JSecurityException* exception=new JSecurityException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JSecurityExceptionTest::~JSecurityExceptionTest(){
        }
    }
}
