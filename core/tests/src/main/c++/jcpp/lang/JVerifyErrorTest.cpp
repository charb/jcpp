#include "jcpp/lang/JVerifyErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JVerifyError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JVerifyErrorTest::JVerifyErrorTest():JSerializableTest(getClazz()){
        }

        void JVerifyErrorTest::equals(JObject* reached, JObject* expected){
            JVerifyError* r=dynamic_cast<JVerifyError*>(reached);
            r->printStackTrace();
            JVerifyError* e=dynamic_cast<JVerifyError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JVerifyErrorTest::getSerializableObject(){
            JVerifyError* cause=new JVerifyError(new JString("This is the cause"));
            JVerifyError* ex=new JVerifyError(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JVerifyErrorTest::~JVerifyErrorTest(){
        }
    }
}
