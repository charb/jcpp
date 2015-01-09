#include "jcpp/lang/JEnumConstantNotPresentExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JEnumConstantNotPresentException.h"
#include "jcpp/JEnumSampleObject.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JEnumConstantNotPresentExceptionTest::JEnumConstantNotPresentExceptionTest():JSerializableTest(getClazz()){
        }

        void JEnumConstantNotPresentExceptionTest::equals(JObject* reached, JObject* expected){
            JEnumConstantNotPresentException* r=dynamic_cast<JEnumConstantNotPresentException*>(reached);
            r->printStackTrace();
            JEnumConstantNotPresentException* e=dynamic_cast<JEnumConstantNotPresentException*>(expected);
            assertEquals(r->getEnumType(),e->getEnumType());
            assertEquals(r->getConstantName(),e->getConstantName());
        }

        JObject* JEnumConstantNotPresentExceptionTest::getSerializableObject(){
            JEnumConstantNotPresentException* exc=new JEnumConstantNotPresentException(JEnumSampleObject::getClazz(),new JString("ENUM6"));
            return exc;
        }

        JEnumConstantNotPresentExceptionTest::~JEnumConstantNotPresentExceptionTest(){
        }
    }
}
