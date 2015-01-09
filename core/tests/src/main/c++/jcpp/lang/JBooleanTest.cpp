#include "jcpp/lang/JBooleanTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JBoolean.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JBooleanTest::JBooleanTest():JSerializableTest(getClazz()){
        }

        JObject* JBooleanTest::getSerializableObject(){
            return new JBoolean(true);
        }

        JBooleanTest::~JBooleanTest(){
        }
    }
}
