#include "jcpp/lang/JIllegalMonitorStateExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalMonitorStateException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalMonitorStateExceptionTest::JIllegalMonitorStateExceptionTest():JSerializableTest(getClazz()){
        }

        void JIllegalMonitorStateExceptionTest::equals(JObject* reached, JObject* expected){
            JIllegalMonitorStateException* r=dynamic_cast<JIllegalMonitorStateException*>(reached);
            r->printStackTrace();
            JIllegalMonitorStateException* e=dynamic_cast<JIllegalMonitorStateException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIllegalMonitorStateExceptionTest::getSerializableObject(){
            JIllegalMonitorStateException* cause=new JIllegalMonitorStateException(new JString("This is the cause"));            
            JIllegalMonitorStateException* exception=new JIllegalMonitorStateException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JIllegalMonitorStateExceptionTest::~JIllegalMonitorStateExceptionTest(){
        }
    }
}
