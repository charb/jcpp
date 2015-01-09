#include "jcpp/lang/JAbstractMethodErrorTest.h"
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

        JAbstractMethodErrorTest::JAbstractMethodErrorTest():JSerializableTest(getClazz()){
        }

        void JAbstractMethodErrorTest::equals(JObject* reached, JObject* expected){
            JAbstractMethodError* r=dynamic_cast<JAbstractMethodError*>(reached);
            r->printStackTrace();
            JAbstractMethodError* e=dynamic_cast<JAbstractMethodError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JAbstractMethodErrorTest::getSerializableObject(){
            JAbstractMethodError* cause=new JAbstractMethodError(new JString("This is the cause"));
            return new JAbstractMethodError(new JString("The exception to test"),cause);
        }

        JAbstractMethodErrorTest::~JAbstractMethodErrorTest(){
        }
    }
}
