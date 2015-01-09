#include "jcpp/lang/JNoSuchFieldErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoSuchFieldError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchFieldErrorTest::JNoSuchFieldErrorTest():JSerializableTest(getClazz()){
        }

        void JNoSuchFieldErrorTest::equals(JObject* reached, JObject* expected){
            JNoSuchFieldError* r=dynamic_cast<JNoSuchFieldError*>(reached);
            r->printStackTrace();
            JNoSuchFieldError* e=dynamic_cast<JNoSuchFieldError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNoSuchFieldErrorTest::getSerializableObject(){
            JNoSuchFieldError* cause=new JNoSuchFieldError(new JString("This is the cause"));            
            JNoSuchFieldError* exception=new JNoSuchFieldError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNoSuchFieldErrorTest::~JNoSuchFieldErrorTest(){
        }
    }
}
