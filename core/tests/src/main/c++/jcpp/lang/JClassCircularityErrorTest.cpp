#include "jcpp/lang/JClassCircularityErrorTest.h"
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

        JClassCircularityErrorTest::JClassCircularityErrorTest():JSerializableTest(getClazz()){
        }

        void JClassCircularityErrorTest::equals(JObject* reached, JObject* expected){
            JClassCircularityError* r=dynamic_cast<JClassCircularityError*>(reached);
            r->printStackTrace();
            JClassCircularityError* e=dynamic_cast<JClassCircularityError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JClassCircularityErrorTest::getSerializableObject(){
            JClassCircularityError* cause=new JClassCircularityError(new JString("This is the cause"));
            JClassCircularityError* exc=new JClassCircularityError(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JClassCircularityErrorTest::~JClassCircularityErrorTest(){
        }
    }
}
