#include "jcpp/lang/JUnsupportedClassVersionErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JUnsupportedClassVersionError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnsupportedClassVersionErrorTest::JUnsupportedClassVersionErrorTest():JSerializableTest(getClazz()){
        }

        void JUnsupportedClassVersionErrorTest::equals(JObject* reached, JObject* expected){
            JUnsupportedClassVersionError* r=dynamic_cast<JUnsupportedClassVersionError*>(reached);
            r->printStackTrace();
            JUnsupportedClassVersionError* e=dynamic_cast<JUnsupportedClassVersionError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUnsupportedClassVersionErrorTest::getSerializableObject(){
            JUnsupportedClassVersionError* cause=new JUnsupportedClassVersionError(new JString("This is the cause"));
            JUnsupportedClassVersionError* ex=new JUnsupportedClassVersionError(new JString("The exception to test"));
            ex->setCause(cause);
            return ex;
        }

        JUnsupportedClassVersionErrorTest::~JUnsupportedClassVersionErrorTest(){
        }
    }
}
