#include "jcpp/util/JHashMapTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JHashMap.h"
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

        JHashMapTest::JHashMapTest():JSerializableTest(getClazz()){
        }

        void JHashMapTest::equals(JObject* reached, JObject* expected){
            JHashMap* r=dynamic_cast<JHashMap*>(reached);
            JHashMap* e=dynamic_cast<JHashMap*>(expected);
            assertEquals(r,e);
        }

        JObject* JHashMapTest::getSerializableObject(){
            JHashMap* a1=new JHashMap();
            a1->put(new JString("index0"),new JSampleObject());
            a1->put(new JString("index1"),new JInteger(0));
            a1->put(new JString("index2"),new JSampleObject());
            a1->put(new JString("index3"),new JHashMap());
            a1->put(new JString("index4"),new JString("index4"));
            a1->put(new JString("index5"),new JString("index5"));
            a1->put(new JString("index6"),new JFloat(78));
            a1->put(new JString("index7"),new JShort((jshort)78));
            a1->put(new JString("index8"),new JArrayList());
            a1->put(new JString("index9"),new JLong(78));
            a1->put(new JString("index10"),new JHashMap());
            return a1;
        }

        JHashMapTest::~JHashMapTest(){
        }
    }
}
