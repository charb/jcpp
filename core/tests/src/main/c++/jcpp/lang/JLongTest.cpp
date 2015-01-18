#include "jcpp/lang/JLongTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JArrays.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JLongTest::JLongTest():JSerializableTest(getClazz()){
        }

        void JLongTest::equals(JObject* reached, JObject* expected){
            JPrimitiveObjectArray* a1=dynamic_cast<JPrimitiveObjectArray*>(reached);
            JPrimitiveObjectArray* a2=dynamic_cast<JPrimitiveObjectArray*>(expected);
            assertTrue(new JString("Asserting that 2 long arrays are equals"),JArrays::equals(a1,a2));
        }

        JObject* JLongTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JLong::getClazz(),3);
            a->set(0,new JLong((jlong)78));
            a->set(1,new JLong(JLong::MAX_VALUE));
            a->set(2,new JLong(JLong::MIN_VALUE));
            return a;
        }

        JLongTest::~JLongTest(){
        }
    }
}
