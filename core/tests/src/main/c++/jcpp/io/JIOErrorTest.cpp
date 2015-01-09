#include "jcpp/io/JIOErrorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JIOError.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{


        JIOErrorTest::JIOErrorTest():JSerializableTest(getClazz()){
        }

        void JIOErrorTest::equals(JObject* reached, JObject* expected){
            JIOError* r=dynamic_cast<JIOError*>(reached);
            r->printStackTrace();
            JIOError* e=dynamic_cast<JIOError*>(expected);
        }

        JObject* JIOErrorTest::getSerializableObject(){
            JIOError* cause=new JIOError();
            JIOError* exception=new JIOError();
            exception->setCause(cause);
            return exception;
        }

        JIOErrorTest::~JIOErrorTest(){
        }
    }
}
