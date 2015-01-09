#include "jcpp/lang/JFloatTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JFloatTest::JFloatTest():JSerializableTest(getClazz()){
        }

        JObject* JFloatTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JFloat::getClazz(),3);
            a->set(0,new JFloat((jfloat)78));
            a->set(1,new JFloat(JFloat::MAX_VALUE));
            a->set(2,new JFloat(JFloat::MIN_VALUE));
            return a;
        }

        JFloatTest::~JFloatTest(){
        }
    }
}
