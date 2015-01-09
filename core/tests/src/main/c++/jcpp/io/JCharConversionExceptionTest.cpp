#include "jcpp/io/JCharConversionExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JCharConversionException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{


        JCharConversionExceptionTest::JCharConversionExceptionTest():JSerializableTest(getClazz()){
        }

        void JCharConversionExceptionTest::equals(JObject* reached, JObject* expected){
            JCharConversionException* r=dynamic_cast<JCharConversionException*>(reached);
            r->printStackTrace();
            JCharConversionException* e=dynamic_cast<JCharConversionException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JCharConversionExceptionTest::getSerializableObject(){
            JCharConversionException* cause=new JCharConversionException(new JString("This is the cause"));
            JCharConversionException* exception=new JCharConversionException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JCharConversionExceptionTest::~JCharConversionExceptionTest(){
        }
    }
}
