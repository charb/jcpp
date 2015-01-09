#include "jcpp/util/JNoSuchElementExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JNoSuchElementException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

        JNoSuchElementExceptionTest::JNoSuchElementExceptionTest():JSerializableTest(getClazz()){
        }

        void JNoSuchElementExceptionTest::equals(JObject* reached, JObject* expected){
            JNoSuchElementException* r=dynamic_cast<JNoSuchElementException*>(reached);
            r->printStackTrace();
            JNoSuchElementException* e=dynamic_cast<JNoSuchElementException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNoSuchElementExceptionTest::getSerializableObject(){
            JNoSuchElementException* cause=new JNoSuchElementException(new JString("This is the cause"));
            JNoSuchElementException* ex=new JNoSuchElementException(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JNoSuchElementExceptionTest::~JNoSuchElementExceptionTest(){
        }
    }
}
