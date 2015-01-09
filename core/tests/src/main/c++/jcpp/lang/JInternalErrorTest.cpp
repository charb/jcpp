#include "jcpp/lang/JInternalErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JInternalError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInternalErrorTest::JInternalErrorTest():JSerializableTest(getClazz()){
        }

        void JInternalErrorTest::equals(JObject* reached, JObject* expected){
            JInternalError* r=dynamic_cast<JInternalError*>(reached);
            r->printStackTrace();
            JInternalError* e=dynamic_cast<JInternalError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JInternalErrorTest::getSerializableObject(){
            JInternalError* cause=new JInternalError(new JString("This is the cause"));            
            JInternalError* exception=new JInternalError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JInternalErrorTest::~JInternalErrorTest(){
        }
    }
}
