#include "jcpp/lang/JUnknownErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JUnknownError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnknownErrorTest::JUnknownErrorTest():JSerializableTest(getClazz()){
        }

        void JUnknownErrorTest::equals(JObject* reached, JObject* expected){
            JUnknownError* r=dynamic_cast<JUnknownError*>(reached);
            r->printStackTrace();
            JUnknownError* e=dynamic_cast<JUnknownError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUnknownErrorTest::getSerializableObject(){
            JUnknownError* cause=new JUnknownError(new JString("This is the cause"));
            JUnknownError* ex=new JUnknownError(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JUnknownErrorTest::~JUnknownErrorTest(){
        }
    }
}
