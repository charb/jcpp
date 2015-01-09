#include "jcpp/lang/JOutOfMemoryErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JOutOfMemoryError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JOutOfMemoryErrorTest::JOutOfMemoryErrorTest():JSerializableTest(getClazz()){
        }

        void JOutOfMemoryErrorTest::equals(JObject* reached, JObject* expected){
            JOutOfMemoryError* r=dynamic_cast<JOutOfMemoryError*>(reached);
            r->printStackTrace();
            JOutOfMemoryError* e=dynamic_cast<JOutOfMemoryError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JOutOfMemoryErrorTest::getSerializableObject(){
            JOutOfMemoryError* cause=new JOutOfMemoryError(new JString("This is the cause"));            
            JOutOfMemoryError* exception=new JOutOfMemoryError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JOutOfMemoryErrorTest::~JOutOfMemoryErrorTest(){
        }
    }
}
