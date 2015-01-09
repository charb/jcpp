#include "jcpp/lang/reflect/JInvocationTargetExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JInvocationTargetException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
    	namespace reflect{
        JInvocationTargetExceptionTest::JInvocationTargetExceptionTest():JSerializableTest(getClazz()){
        }

        void JInvocationTargetExceptionTest::equals(JObject* reached, JObject* expected){
            JInvocationTargetException* r=dynamic_cast<JInvocationTargetException*>(reached);
            r->printStackTrace();
            JInvocationTargetException* e=dynamic_cast<JInvocationTargetException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getTargetException()->getMessage(),e->getTargetException()->getMessage());
        }

        JObject* JInvocationTargetExceptionTest::getSerializableObject(){
            JInvocationTargetException* cause=new JInvocationTargetException(null,new JString("This is the cause"));
            return new JInvocationTargetException(cause,new JString("The exception to test"));
        }

        JInvocationTargetExceptionTest::~JInvocationTargetExceptionTest(){
        }
    	}
    }
}
