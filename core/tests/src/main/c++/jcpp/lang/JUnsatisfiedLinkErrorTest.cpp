#include "jcpp/lang/JUnsatisfiedLinkErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JUnsatisfiedLinkError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnsatisfiedLinkErrorTest::JUnsatisfiedLinkErrorTest():JSerializableTest(getClazz()){
        }

        void JUnsatisfiedLinkErrorTest::equals(JObject* reached, JObject* expected){
            JUnsatisfiedLinkError* r=dynamic_cast<JUnsatisfiedLinkError*>(reached);
            r->printStackTrace();
            JUnsatisfiedLinkError* e=dynamic_cast<JUnsatisfiedLinkError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUnsatisfiedLinkErrorTest::getSerializableObject(){
            JUnsatisfiedLinkError* cause=new JUnsatisfiedLinkError(new JString("This is the cause"));
            JUnsatisfiedLinkError* ex=new JUnsatisfiedLinkError(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JUnsatisfiedLinkErrorTest::~JUnsatisfiedLinkErrorTest(){
        }
    }
}
