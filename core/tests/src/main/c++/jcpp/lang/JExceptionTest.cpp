#include "jcpp/lang/JExceptionTest.h"
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

        JExceptionTest::JExceptionTest():JSerializableTest(getClazz()){
        }

        void JExceptionTest::equals(JObject* reached, JObject* expected){
            JException* r=dynamic_cast<JException*>(reached);
            r->printStackTrace();
            JException* e=dynamic_cast<JException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JExceptionTest::getSerializableObject(){
            JException* cause=new JException(new JString("This is the cause"));
            return new JException(new JString("The exception to test"),cause);
        }

        JExceptionTest::~JExceptionTest(){
        }
    }
}
