#include "jcpp/util/JVectorTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JVector.h"
#include "jcpp/JSampleObject.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

        JVectorTest::JVectorTest():JSerializableTest(getClazz()){
        }

        void JVectorTest::equals(JObject* reached, JObject* expected){
            JVector* r=dynamic_cast<JVector*>(reached);
            JVector* e=dynamic_cast<JVector*>(expected);
            assertEquals(r,e);
        }

        JObject* JVectorTest::getSerializableObject(){
            JVector* a1=new JVector();
            a1->add(new JSampleObject());
            a1->add(new JInteger(0));
            a1->add(new JSampleObject());
            a1->add(new JVector());
            a1->add(new JString("index4"));
            a1->add(new JString("index5"));
            a1->add(new JFloat(78));
            a1->add(new JShort((jshort)78));
            a1->add(new JVector());
            a1->add(new JLong(78));
            return a1;
        }

        JVectorTest::~JVectorTest(){
        }
    }
}
