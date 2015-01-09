#include "jcpp/io/JEOFExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JEOFException.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JEOFExceptionTest::JEOFExceptionTest():JSerializableTest(getClazz()){
        }

        void JEOFExceptionTest::equals(JObject* reached, JObject* expected){
            JEOFException* r=dynamic_cast<JEOFException*>(reached);
            r->printStackTrace();
            JEOFException* e=dynamic_cast<JEOFException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JEOFExceptionTest::getSerializableObject(){
            JEOFException* cause=new JEOFException(new JString("This is the cause"));
            JEOFException* exception=new JEOFException(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JEOFExceptionTest::~JEOFExceptionTest(){
        }
    }
}
