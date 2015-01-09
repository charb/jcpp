#include "jcpp/util/JConcurrentModificationExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JConcurrentModificationException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

        JConcurrentModificationExceptionTest::JConcurrentModificationExceptionTest():JSerializableTest(getClazz()){
        }

        void JConcurrentModificationExceptionTest::equals(JObject* reached, JObject* expected){
            JConcurrentModificationException* r=dynamic_cast<JConcurrentModificationException*>(reached);
            r->printStackTrace();
            JConcurrentModificationException* e=dynamic_cast<JConcurrentModificationException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JConcurrentModificationExceptionTest::getSerializableObject(){
            JConcurrentModificationException* cause=new JConcurrentModificationException(new JString("This is the cause"));
            JConcurrentModificationException* ex=new JConcurrentModificationException(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JConcurrentModificationExceptionTest::~JConcurrentModificationExceptionTest(){
        }
    }
}
