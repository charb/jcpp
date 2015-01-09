#include "jcpp/lang/JTypeNotPresentExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JTypeNotPresentException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JTypeNotPresentExceptionTest::JTypeNotPresentExceptionTest():JSerializableTest(getClazz()){
        }

        void JTypeNotPresentExceptionTest::equals(JObject* reached, JObject* expected){
            JTypeNotPresentException* r=dynamic_cast<JTypeNotPresentException*>(reached);
            r->printStackTrace();
            JTypeNotPresentException* e=dynamic_cast<JTypeNotPresentException*>(expected);
            assertEquals(r->getTypeName(),e->getTypeName());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JTypeNotPresentExceptionTest::getSerializableObject(){
            JException* cause=new JException(new JString("This is the cause"));
            JTypeNotPresentException* exception=new JTypeNotPresentException(new JString("TYPE_NAME"),null);
            exception->setCause(cause);
            return exception;
        }

        JTypeNotPresentExceptionTest::~JTypeNotPresentExceptionTest(){
        }
    }
}
