#include "jcpp/lang/JNoSuchMethodErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoSuchMethodError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{


        JNoSuchMethodErrorTest::JNoSuchMethodErrorTest():JSerializableTest(getClazz()){
        }

        void JNoSuchMethodErrorTest::equals(JObject* reached, JObject* expected){
            JNoSuchMethodError* r=dynamic_cast<JNoSuchMethodError*>(reached);
            r->printStackTrace();
            JNoSuchMethodError* e=dynamic_cast<JNoSuchMethodError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNoSuchMethodErrorTest::getSerializableObject(){
            JNoSuchMethodError* cause=new JNoSuchMethodError(new JString("This is the cause"));            
            JNoSuchMethodError* exception=new JNoSuchMethodError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNoSuchMethodErrorTest::~JNoSuchMethodErrorTest(){
        }
    }
}
