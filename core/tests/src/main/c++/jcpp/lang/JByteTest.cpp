#include "jcpp/lang/JByteTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrays.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{

        JByteTest::JByteTest():JSerializableTest(getClazz()){
        }

        void JByteTest::equals(JObject* reached, JObject* expected){
            JPrimitiveObjectArray* a1=dynamic_cast<JPrimitiveObjectArray*>(reached);
            JPrimitiveObjectArray* a2=dynamic_cast<JPrimitiveObjectArray*>(expected);
            assertTrue(new JString("Asserting that 2 byte arrays are equals"),JArrays::equals(a1,a2));
        }

        JObject* JByteTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JByte::getClazz(),3);
            a->set(0,new JByte(78));
            a->set(1,new JByte(JByte::MAX_VALUE));
            a->set(2,new JByte(JByte::MIN_VALUE));
            return a;
        }

        JByteTest::~JByteTest(){
        }
    }
}
