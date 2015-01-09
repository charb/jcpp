#include "jcpp/lang/JNoSuchFieldExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoSuchFieldException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchFieldExceptionTest::JNoSuchFieldExceptionTest():JSerializableTest(getClazz()){
        }

        void JNoSuchFieldExceptionTest::equals(JObject* reached, JObject* expected){
            JNoSuchFieldException* r=dynamic_cast<JNoSuchFieldException*>(reached);
            r->printStackTrace();
            JNoSuchFieldException* e=dynamic_cast<JNoSuchFieldException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNoSuchFieldExceptionTest::getSerializableObject(){
            JNoSuchFieldException* cause=new JNoSuchFieldException(new JString("This is the cause"));            
            JNoSuchFieldException* exception=new JNoSuchFieldException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNoSuchFieldExceptionTest::~JNoSuchFieldExceptionTest(){
        }
    }
}
