#include "jcpp/lang/JInstantiationExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JInstantiationException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInstantiationExceptionTest::JInstantiationExceptionTest():JSerializableTest(getClazz()){
        }

        void JInstantiationExceptionTest::equals(JObject* reached, JObject* expected){
            JInstantiationException* r=dynamic_cast<JInstantiationException*>(reached);
            r->printStackTrace();
            JInstantiationException* e=dynamic_cast<JInstantiationException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInstantiationExceptionTest::getSerializableObject(){
            JInstantiationException* cause=new JInstantiationException(new JString("This is the cause"));            
            JInstantiationException* exception=new JInstantiationException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JInstantiationExceptionTest::~JInstantiationExceptionTest(){
        }
    }
}
