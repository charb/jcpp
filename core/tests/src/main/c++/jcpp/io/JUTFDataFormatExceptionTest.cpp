#include "jcpp/io/JUTFDataFormatExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JUTFDataFormatException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JUTFDataFormatExceptionTest::JUTFDataFormatExceptionTest():JSerializableTest(getClazz()){
        }

        void JUTFDataFormatExceptionTest::equals(JObject* reached, JObject* expected){
            JUTFDataFormatException* r=dynamic_cast<JUTFDataFormatException*>(reached);
            r->printStackTrace();
            JUTFDataFormatException* e=dynamic_cast<JUTFDataFormatException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JUTFDataFormatExceptionTest::getSerializableObject(){
            JUTFDataFormatException* cause=new JUTFDataFormatException(new JString("This is the cause"));
            JUTFDataFormatException* exception=new JUTFDataFormatException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JUTFDataFormatExceptionTest::~JUTFDataFormatExceptionTest(){
        }
    }
}
