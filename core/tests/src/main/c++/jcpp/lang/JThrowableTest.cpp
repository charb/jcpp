#include "jcpp/lang/JThrowableTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JThrowable.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

    	JThrowableTest::JThrowableTest():JSerializableTest(getClazz()){
        }

        void JThrowableTest::equals(JObject* reached, JObject* expected){
            JThrowable* r=dynamic_cast<JThrowable*>(reached);
            r->printStackTrace();
            JThrowable* e=dynamic_cast<JThrowable*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JThrowableTest::getSerializableObject(){
            JThrowable* cause=new JThrowable(new JString("This is the cause"));
            return new JThrowable(new JString("The exception to test"),cause);
        }

        JThrowableTest::~JThrowableTest(){
        }
    }
}
