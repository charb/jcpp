#include "jcpp/lang/JIllegalAccessErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JIllegalAccessError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalAccessErrorTest::JIllegalAccessErrorTest():JSerializableTest(getClazz()){
        }

        void JIllegalAccessErrorTest::equals(JObject* reached, JObject* expected){
            JIllegalAccessError* r=dynamic_cast<JIllegalAccessError*>(reached);
            r->printStackTrace();
            JIllegalAccessError* e=dynamic_cast<JIllegalAccessError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JIllegalAccessErrorTest::getSerializableObject(){
            JIllegalAccessError* cause=new JIllegalAccessError(new JString("This is the cause"));            
            return new JIllegalAccessError(new JString("The exception to test"),cause);
        }

        JIllegalAccessErrorTest::~JIllegalAccessErrorTest(){
        }
    }
}
