#include "jcpp/lang/JByteTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JByteTest::JByteTest():JSerializableTest(getClazz()){
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
