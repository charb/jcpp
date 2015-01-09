#include "jcpp/util/concurrent/JBrokenBarrierExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/JBrokenBarrierException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JBrokenBarrierExceptionTest::JBrokenBarrierExceptionTest():JSerializableTest(getClazz()){
            }

            void JBrokenBarrierExceptionTest::equals(JObject* reached, JObject* expected){
                JBrokenBarrierException* r=dynamic_cast<JBrokenBarrierException*>(reached);
                r->printStackTrace();
                JBrokenBarrierException* e=dynamic_cast<JBrokenBarrierException*>(expected);
                assertEquals(r->getMessage(),e->getMessage());
                assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
            }

            JObject* JBrokenBarrierExceptionTest::getSerializableObject(){
                JBrokenBarrierException* cause=new JBrokenBarrierException(new JString("This is the cause"));
                JBrokenBarrierException* ex=new JBrokenBarrierException(new JString("The exception to test"));
                ex->setCause(cause);
                return ex;
            }

            JBrokenBarrierExceptionTest::~JBrokenBarrierExceptionTest(){
            }
        }
    }
}
