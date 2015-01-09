#include "jcpp/lang/JErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JErrorTest::JErrorTest():JSerializableTest(getClazz()){
        }

        void JErrorTest::equals(JObject* reached, JObject* expected){
            JError* r=dynamic_cast<JError*>(reached);
            r->printStackTrace();
            JError* e=dynamic_cast<JError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JErrorTest::getSerializableObject(){
            JError* cause=new JError(new JString("This is the cause"));
            return new JError(new JString("The exception to test"),cause);
        }

        JErrorTest::~JErrorTest(){
        }
    }
}
