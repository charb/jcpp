#include "jcpp/util/concurrent/JExecutionExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/JExecutionException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JExecutionExceptionTest::JExecutionExceptionTest():JSerializableTest(getClazz()){
            }

            void JExecutionExceptionTest::equals(JObject* reached, JObject* expected){
                JExecutionException* r=dynamic_cast<JExecutionException*>(reached);
                r->printStackTrace();
                JExecutionException* e=dynamic_cast<JExecutionException*>(expected);
                assertEquals(r->getMessage(),e->getMessage());
                assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
            }

            JObject* JExecutionExceptionTest::getSerializableObject(){
                JExecutionException* cause=new JExecutionException(new JString("This is the cause"));
                JExecutionException* ex=new JExecutionException(new JString("The exception to test"));
                ex->setCause(cause);
                return ex;
            }

            JExecutionExceptionTest::~JExecutionExceptionTest(){
            }
        }
    }
}
