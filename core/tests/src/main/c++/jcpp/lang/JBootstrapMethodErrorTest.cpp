#include "jcpp/lang/JBootstrapMethodErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JBootstrapMethodErrorTest::JBootstrapMethodErrorTest():JSerializableTest(getClazz()){
        }

        void JBootstrapMethodErrorTest::equals(JObject* reached, JObject* expected){
            JBootstrapMethodError* r=dynamic_cast<JBootstrapMethodError*>(reached);
            r->printStackTrace();
            JBootstrapMethodError* e=dynamic_cast<JBootstrapMethodError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JBootstrapMethodErrorTest::getSerializableObject(){
            JBootstrapMethodError* cause=new JBootstrapMethodError(new JString("This is the cause"));
            JBootstrapMethodError* exc=new JBootstrapMethodError(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JBootstrapMethodErrorTest::~JBootstrapMethodErrorTest(){
        }
    }
}
