#include "jcpp/lang/JLinkageErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JLinkageError.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JLinkageErrorTest::JLinkageErrorTest():JSerializableTest(getClazz()){
        }

        void JLinkageErrorTest::equals(JObject* reached, JObject* expected){
            JLinkageError* r=dynamic_cast<JLinkageError*>(reached);
            r->printStackTrace();
            JLinkageError* e=dynamic_cast<JLinkageError*>(expected);
            assertEquals(r->getMessage(),e->getMessage());
            assertEquals(r->getCause()->getMessage(),e->getCause()->getMessage());
        }

        JObject* JLinkageErrorTest::getSerializableObject(){
            JLinkageError* cause=new JLinkageError(new JString("This is the cause"));            
            JLinkageError* exception=new JLinkageError(new JString("The exception to test"));
            exception->setCause(cause);
            return exception;
        }

        JLinkageErrorTest::~JLinkageErrorTest(){
        }
    }
}
