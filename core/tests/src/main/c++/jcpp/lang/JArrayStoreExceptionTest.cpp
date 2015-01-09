#include "jcpp/lang/JArrayStoreExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JArrayStoreException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JArrayStoreExceptionTest::JArrayStoreExceptionTest():JSerializableTest(getClazz()){
        }

        void JArrayStoreExceptionTest::equals(JObject* reached, JObject* expected){
            JArrayStoreException* r=dynamic_cast<JArrayStoreException*>(reached);
            r->printStackTrace();
            JArrayStoreException* e=dynamic_cast<JArrayStoreException*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JArrayStoreExceptionTest::getSerializableObject(){
            JArrayStoreException* cause=new JArrayStoreException(new JString("This is the cause"));
            JArrayStoreException* exc=new JArrayStoreException(new JString("The exception to test"));
            exc->setCause(cause);
            return exc;
        }

        JArrayStoreExceptionTest::~JArrayStoreExceptionTest(){
        }
    }
}
