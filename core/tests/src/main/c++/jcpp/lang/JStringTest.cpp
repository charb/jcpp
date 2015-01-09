#include "jcpp/lang/JStringTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStringTest::JStringTest(JString* name):JAbstractTest(getClazz(),name){
        }

        void JStringTest::testNewString(){
        }

        JStringTest::~JStringTest(){
        }
    }
}
