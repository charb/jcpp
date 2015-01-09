#include "jcpp/util/JArrayListTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JArrayList.h"
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

        JArrayListTest::JArrayListTest():JSerializableTest(getClazz()){
        }

        void JArrayListTest::equals(JObject* reached, JObject* expected){
            JArrayList* r=dynamic_cast<JArrayList*>(reached);
            JArrayList* e=dynamic_cast<JArrayList*>(expected);
            assertEquals(r,e);
        }

        JObject* JArrayListTest::getSerializableObject(){
            JArrayList* a1=new JArrayList();
            a1->add(new JSampleObject());
            a1->add(new JInteger(0));
            a1->add(new JSampleObject());
            a1->add(new JArrayList());
            a1->add(new JString("index4"));
            a1->add(new JString("index5"));
            a1->add(new JFloat(78));
            a1->add(new JShort((jshort)78));
            a1->add(new JArrayList());
            a1->add(new JLong(78));
            return a1;
        }

        JArrayListTest::~JArrayListTest(){
        }
    }
}
