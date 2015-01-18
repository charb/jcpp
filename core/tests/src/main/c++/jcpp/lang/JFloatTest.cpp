#include "jcpp/lang/JFloatTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JArrays.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JFloatTest::JFloatTest():JSerializableTest(getClazz()){
        }

        void JFloatTest::equals(JObject* reached, JObject* expected){
            JPrimitiveObjectArray* a1=dynamic_cast<JPrimitiveObjectArray*>(reached);
            JPrimitiveObjectArray* a2=dynamic_cast<JPrimitiveObjectArray*>(expected);
            assertTrue(new JString("Asserting that 2 float arrays are equals"),JArrays::equals(a1,a2));
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
