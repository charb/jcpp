#include "jcpp/lang/JCloneNotSupportedExceptionTest.h"
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

        JCloneNotSupportedExceptionTest::JCloneNotSupportedExceptionTest():JSerializableTest(getClazz()){
        }

        void JCloneNotSupportedExceptionTest::equals(JObject* reached, JObject* expected){
            JCloneNotSupportedException* r=dynamic_cast<JCloneNotSupportedException*>(reached);
            r->printStackTrace();
            JCloneNotSupportedException* e=dynamic_cast<JCloneNotSupportedException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JCloneNotSupportedExceptionTest::getSerializableObject(){
            JCloneNotSupportedException* cause=new JCloneNotSupportedException(new JString("This is the cause"));
            JCloneNotSupportedException* exc=new JCloneNotSupportedException(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JCloneNotSupportedExceptionTest::~JCloneNotSupportedExceptionTest(){
        }
    }
}
