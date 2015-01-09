#include "jcpp/lang/JNoClassDefFoundErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoClassDefFoundError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoClassDefFoundErrorTest::JNoClassDefFoundErrorTest():JSerializableTest(getClazz()){
        }

        void JNoClassDefFoundErrorTest::equals(JObject* reached, JObject* expected){
            JNoClassDefFoundError* r=dynamic_cast<JNoClassDefFoundError*>(reached);
            r->printStackTrace();
            JNoClassDefFoundError* e=dynamic_cast<JNoClassDefFoundError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JNoClassDefFoundErrorTest::getSerializableObject(){
            JNoClassDefFoundError* cause=new JNoClassDefFoundError(new JString("This is the cause"));            
            JNoClassDefFoundError* exception=new JNoClassDefFoundError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JNoClassDefFoundErrorTest::~JNoClassDefFoundErrorTest(){
        }
    }
}
