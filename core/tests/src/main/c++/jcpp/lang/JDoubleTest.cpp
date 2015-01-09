#include "jcpp/lang/JDoubleTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JDoubleTest::JDoubleTest():JSerializableTest(getClazz()){
        }

        JObject* JDoubleTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JDouble::getClazz(),3);
            a->set(0,new JDouble((jdouble)78));
            a->set(1,new JDouble(JDouble::MAX_VALUE));
            a->set(2,new JDouble(JDouble::MIN_VALUE));
            return a;
        }

        JDoubleTest::~JDoubleTest(){
        }
    }
}
