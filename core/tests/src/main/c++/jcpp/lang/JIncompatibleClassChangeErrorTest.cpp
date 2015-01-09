#include "jcpp/lang/JIncompatibleClassChangeErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIncompatibleClassChangeErrorTest::JIncompatibleClassChangeErrorTest():JSerializableTest(getClazz()){
        }

        void JIncompatibleClassChangeErrorTest::equals(JObject* reached, JObject* expected){
            JIncompatibleClassChangeError* r=dynamic_cast<JIncompatibleClassChangeError*>(reached);
            r->printStackTrace();
            JIncompatibleClassChangeError* e=dynamic_cast<JIncompatibleClassChangeError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIncompatibleClassChangeErrorTest::getSerializableObject(){
            JIncompatibleClassChangeError* cause=new JIncompatibleClassChangeError(new JString("This is the cause"));            
            JIncompatibleClassChangeError* exception=new JIncompatibleClassChangeError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIncompatibleClassChangeErrorTest::~JIncompatibleClassChangeErrorTest(){
        }
    }
}
