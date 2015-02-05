#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/net/JSocketTimeoutExceptionTest.h"
#include "jcpp/net/JSocketTimeoutException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{

    	JSocketTimeoutExceptionTest::JSocketTimeoutExceptionTest():JSerializableTest(getClazz()){
        }

        void JSocketTimeoutExceptionTest::equals(JObject* reached, JObject* expected){
        	JSocketTimeoutException* r=dynamic_cast<JSocketTimeoutException*>(reached);
            r->printStackTrace();
            JSocketTimeoutException* e=dynamic_cast<JSocketTimeoutException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JSocketTimeoutExceptionTest::getSerializableObject(){
        	JSocketTimeoutException* cause=new JSocketTimeoutException(new JString("This is the cause"));
        	JSocketTimeoutException* exception=new JSocketTimeoutException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JSocketTimeoutExceptionTest::~JSocketTimeoutExceptionTest(){
        }
    }
}
