#include "jcpp/lang/JClassFormatErrorTest.h"
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

        JClassFormatErrorTest::JClassFormatErrorTest():JSerializableTest(getClazz()){
        }

        void JClassFormatErrorTest::equals(JObject* reached, JObject* expected){
            JClassFormatError* r=dynamic_cast<JClassFormatError*>(reached);
            r->printStackTrace();
            JClassFormatError* e=dynamic_cast<JClassFormatError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JClassFormatErrorTest::getSerializableObject(){
            JClassFormatError* cause=new JClassFormatError(new JString("This is the cause"));
            JClassFormatError* exc=new JClassFormatError(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JClassFormatErrorTest::~JClassFormatErrorTest(){
        }
    }
}
