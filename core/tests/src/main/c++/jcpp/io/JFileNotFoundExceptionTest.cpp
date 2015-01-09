#include "jcpp/io/JFileNotFoundExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JFileNotFoundException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{


        JFileNotFoundExceptionTest::JFileNotFoundExceptionTest():JSerializableTest(getClazz()){
        }

        void JFileNotFoundExceptionTest::equals(JObject* reached, JObject* expected){
            JFileNotFoundException* r=dynamic_cast<JFileNotFoundException*>(reached);
            r->printStackTrace();
            JFileNotFoundException* e=dynamic_cast<JFileNotFoundException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JFileNotFoundExceptionTest::getSerializableObject(){
            JFileNotFoundException* cause=new JFileNotFoundException(new JString("This is the cause"));
            JFileNotFoundException* exception=new JFileNotFoundException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JFileNotFoundExceptionTest::~JFileNotFoundExceptionTest(){
        }
    }
}
