#include "jcpp/lang/JInstantiationErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JInstantiationError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInstantiationErrorTest::JInstantiationErrorTest():JSerializableTest(getClazz()){
        }

        void JInstantiationErrorTest::equals(JObject* reached, JObject* expected){
            JInstantiationError* r=dynamic_cast<JInstantiationError*>(reached);
            r->printStackTrace();
            JInstantiationError* e=dynamic_cast<JInstantiationError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInstantiationErrorTest::getSerializableObject(){
            JInstantiationError* cause=new JInstantiationError(new JString("This is the cause"));            
            JInstantiationError* exception=new JInstantiationError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JInstantiationErrorTest::~JInstantiationErrorTest(){
        }
    }
}
