#include "jcpp/lang/reflect/JMalformedParameterizedTypeExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JMalformedParameterizedTypeException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{
        JMalformedParameterizedTypeExceptionTest::JMalformedParameterizedTypeExceptionTest():JSerializableTest(getClazz()){
        }

        void JMalformedParameterizedTypeExceptionTest::equals(JObject* reached, JObject* expected){
            JMalformedParameterizedTypeException* r=dynamic_cast<JMalformedParameterizedTypeException*>(reached);
            r->printStackTrace();
            JMalformedParameterizedTypeException* e=dynamic_cast<JMalformedParameterizedTypeException*>(expected);
            assertEquals(r->getMessage(),null);
            assertEquals(e->getMessage(),null);
            assertEquals(r->getCause()->getMessage(),null);
            assertEquals(e->getCause()->getMessage(),null);
        }

        JObject* JMalformedParameterizedTypeExceptionTest::getSerializableObject(){
            JMalformedParameterizedTypeException* cause=new JMalformedParameterizedTypeException();
            JMalformedParameterizedTypeException* exc=new JMalformedParameterizedTypeException();
            exc->setCause(cause);
            return exc;
        }

        JMalformedParameterizedTypeExceptionTest::~JMalformedParameterizedTypeExceptionTest(){
        }
    }
}
}
