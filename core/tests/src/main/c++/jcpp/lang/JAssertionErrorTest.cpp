#include "jcpp/lang/JAssertionErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JAssertionError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JAssertionErrorTest::JAssertionErrorTest():JSerializableTest(getClazz()){
        }

        void JAssertionErrorTest::equals(JObject* reached, JObject* expected){
            JAssertionError* r=dynamic_cast<JAssertionError*>(reached);
            r->printStackTrace();
            JAssertionError* e=dynamic_cast<JAssertionError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JAssertionErrorTest::getSerializableObject(){
            JAssertionError* cause=new JAssertionError(new JString("This is the cause"));
            JAssertionError* exc=new JAssertionError(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JAssertionErrorTest::~JAssertionErrorTest(){
        }
    }
}
