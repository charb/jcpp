#include "jcpp/lang/JArrayIndexOutOfBoundsExceptionTest.h"
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

        JArrayIndexOutOfBoundsExceptionTest::JArrayIndexOutOfBoundsExceptionTest():JSerializableTest(getClazz()){
        }

        void JArrayIndexOutOfBoundsExceptionTest::equals(JObject* reached, JObject* expected){
            JArrayIndexOutOfBoundsException* r=dynamic_cast<JArrayIndexOutOfBoundsException*>(reached);
            r->printStackTrace();
            JArrayIndexOutOfBoundsException* e=dynamic_cast<JArrayIndexOutOfBoundsException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JArrayIndexOutOfBoundsExceptionTest::getSerializableObject(){
            JArrayIndexOutOfBoundsException* cause=new JArrayIndexOutOfBoundsException(new JString("This is the cause"));
            JArrayIndexOutOfBoundsException* exc=new JArrayIndexOutOfBoundsException(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JArrayIndexOutOfBoundsExceptionTest::~JArrayIndexOutOfBoundsExceptionTest(){
        }
    }
}
