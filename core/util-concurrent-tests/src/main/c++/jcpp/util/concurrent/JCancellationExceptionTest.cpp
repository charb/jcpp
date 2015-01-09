#include "jcpp/util/concurrent/JCancellationExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/JCancellationException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JCancellationExceptionTest::JCancellationExceptionTest():JSerializableTest(getClazz()){
            }

            void JCancellationExceptionTest::equals(JObject* reached, JObject* expected){
                JCancellationException* r=dynamic_cast<JCancellationException*>(reached);
                r->printStackTrace();
                JCancellationException* e=dynamic_cast<JCancellationException*>(expected);
                assertEquals(r->getMessage(),e->getMessage());
                assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
            }

            JObject* JCancellationExceptionTest::getSerializableObject(){
                JCancellationException* cause=new JCancellationException(new JString("This is the cause"));
                JCancellationException* ex=new JCancellationException(new JString("The exception to test"));
                ex->setCause(cause);
                return ex;
            }

            JCancellationExceptionTest::~JCancellationExceptionTest(){
            }
        }
    }
}
