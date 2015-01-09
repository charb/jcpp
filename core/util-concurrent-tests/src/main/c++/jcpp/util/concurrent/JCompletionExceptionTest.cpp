#include "jcpp/util/concurrent/JCompletionExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/JCompletionException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JCompletionExceptionTest::JCompletionExceptionTest():JSerializableTest(getClazz()){
            }

            void JCompletionExceptionTest::equals(JObject* reached, JObject* expected){
                JCompletionException* r=dynamic_cast<JCompletionException*>(reached);
                r->printStackTrace();
                JCompletionException* e=dynamic_cast<JCompletionException*>(expected);
                assertEquals(r->getMessage(),e->getMessage());
                assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
            }

            JObject* JCompletionExceptionTest::getSerializableObject(){
                JCompletionException* cause=new JCompletionException(new JString("This is the cause"));
                JCompletionException* ex=new JCompletionException(new JString("The exception to test"));
                ex->setCause(cause);
                return ex;
            }

            JCompletionExceptionTest::~JCompletionExceptionTest(){
            }
        }
    }
}
