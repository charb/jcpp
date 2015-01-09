#include "jcpp/util/concurrent/JRejectedExecutionExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/JRejectedExecutionException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JRejectedExecutionExceptionTest::JRejectedExecutionExceptionTest():JSerializableTest(getClazz()){
            }

            void JRejectedExecutionExceptionTest::equals(JObject* reached, JObject* expected){
                JRejectedExecutionException* r=dynamic_cast<JRejectedExecutionException*>(reached);
                r->printStackTrace();
                JRejectedExecutionException* e=dynamic_cast<JRejectedExecutionException*>(expected);
                assertEquals(r->getMessage(),e->getMessage());
                assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
            }

            JObject* JRejectedExecutionExceptionTest::getSerializableObject(){
                JRejectedExecutionException* cause=new JRejectedExecutionException(new JString("This is the cause"));
                JRejectedExecutionException* ex=new JRejectedExecutionException(new JString("The exception to test"));
                ex->setCause(cause);
                return ex;
            }

            JRejectedExecutionExceptionTest::~JRejectedExecutionExceptionTest(){
            }
        }
    }
}
