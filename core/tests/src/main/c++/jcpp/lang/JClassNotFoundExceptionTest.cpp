#include "jcpp/lang/JClassNotFoundExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JClassNotFoundExceptionTest::JClassNotFoundExceptionTest():JSerializableTest(getClazz()){
        }

        void JClassNotFoundExceptionTest::equals(JObject* reached, JObject* expected){
            JClassNotFoundException* r=dynamic_cast<JClassNotFoundException*>(reached);
            r->printStackTrace();
            JClassNotFoundException* e=dynamic_cast<JClassNotFoundException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getException()->getMessage(),e->getException()->getMessage());
        }

        JObject* JClassNotFoundExceptionTest::getSerializableObject(){
            JClassNotFoundException* cause=new JClassNotFoundException(new JString("This is the cause"));
            JClassNotFoundException* exc=new JClassNotFoundException(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JClassNotFoundExceptionTest::~JClassNotFoundExceptionTest(){
        }
    }
}
