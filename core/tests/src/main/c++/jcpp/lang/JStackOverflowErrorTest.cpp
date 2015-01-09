#include "jcpp/lang/JStackOverflowErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStackOverflowError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStackOverflowErrorTest::JStackOverflowErrorTest():JSerializableTest(getClazz()){
        }

        void JStackOverflowErrorTest::equals(JObject* reached, JObject* expected){
            JStackOverflowError* r=dynamic_cast<JStackOverflowError*>(reached);
            r->printStackTrace();
            JStackOverflowError* e=dynamic_cast<JStackOverflowError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JStackOverflowErrorTest::getSerializableObject(){
            JStackOverflowError* cause=new JStackOverflowError(new JString("This is the cause"));            
            JStackOverflowError* exception=new JStackOverflowError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JStackOverflowErrorTest::~JStackOverflowErrorTest(){
        }
    }
}
