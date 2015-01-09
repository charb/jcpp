#include "jcpp/lang/JIndexOutOfBoundsExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

    	JIndexOutOfBoundsExceptionTest::JIndexOutOfBoundsExceptionTest():JSerializableTest(getClazz()){
        }

        void JIndexOutOfBoundsExceptionTest::equals(JObject* reached, JObject* expected){
            JIndexOutOfBoundsException* r=dynamic_cast<JIndexOutOfBoundsException*>(reached);
            r->printStackTrace();
            JIndexOutOfBoundsException* e=dynamic_cast<JIndexOutOfBoundsException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIndexOutOfBoundsExceptionTest::getSerializableObject(){
            JIndexOutOfBoundsException* cause=new JIndexOutOfBoundsException(new JString("This is the cause"));            
            JIndexOutOfBoundsException* exception=new JIndexOutOfBoundsException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIndexOutOfBoundsExceptionTest::~JIndexOutOfBoundsExceptionTest(){
        }
    }
}
