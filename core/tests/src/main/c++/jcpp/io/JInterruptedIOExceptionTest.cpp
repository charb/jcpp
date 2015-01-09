#include "jcpp/io/JInterruptedIOExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JInterruptedIOException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JInterruptedIOExceptionTest::JInterruptedIOExceptionTest():JSerializableTest(getClazz()){
        }

        void JInterruptedIOExceptionTest::equals(JObject* reached, JObject* expected){
            JInterruptedIOException* r=dynamic_cast<JInterruptedIOException*>(reached);
            r->printStackTrace();
            JInterruptedIOException* e=dynamic_cast<JInterruptedIOException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getBytesTransferred(),e->getBytesTransferred());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInterruptedIOExceptionTest::getSerializableObject(){
            JInterruptedIOException* cause=new JInterruptedIOException(new JString("This is the cause"));
            cause->setBytesTransferred(78);
            JInterruptedIOException* exception=new JInterruptedIOException(new JString("The exception to test"));
            exception->setBytesTransferred(78);
            exception->setCause(cause);
            return exception;
        }

        JInterruptedIOExceptionTest::~JInterruptedIOExceptionTest(){
        }
    }
}
