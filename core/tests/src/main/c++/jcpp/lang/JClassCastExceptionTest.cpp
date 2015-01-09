#include "jcpp/lang/JClassCastExceptionTest.h"
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

        JClassCastExceptionTest::JClassCastExceptionTest():JSerializableTest(getClazz()){
        }

        void JClassCastExceptionTest::equals(JObject* reached, JObject* expected){
            JClassCastException* r=dynamic_cast<JClassCastException*>(reached);
            r->printStackTrace();
            JClassCastException* e=dynamic_cast<JClassCastException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JClassCastExceptionTest::getSerializableObject(){
            JClassCastException* cause=new JClassCastException(new JString("This is the cause"));
            JClassCastException* exc=new JClassCastException(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JClassCastExceptionTest::~JClassCastExceptionTest(){
        }
    }
}
