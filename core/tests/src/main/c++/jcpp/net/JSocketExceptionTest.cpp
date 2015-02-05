#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/net/JSocketExceptionTest.h"
#include "jcpp/net/JSocketException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{

    	JSocketExceptionTest::JSocketExceptionTest():JSerializableTest(getClazz()){
        }

        void JSocketExceptionTest::equals(JObject* reached, JObject* expected){
        	JSocketException* r=dynamic_cast<JSocketException*>(reached);
            r->printStackTrace();
            JSocketException* e=dynamic_cast<JSocketException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JSocketExceptionTest::getSerializableObject(){
        	JSocketException* cause=new JSocketException(new JString("This is the cause"));
        	JSocketException* exception=new JSocketException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JSocketExceptionTest::~JSocketExceptionTest(){
        }
    }
}
