#include "jcpp/util/concurrent/atomic/JAtomicIntegerArrayTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicIntegerArray.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

                JAtomicIntegerArrayTest::JAtomicIntegerArrayTest():JSerializableTest(getClazz()){
                }

                void JAtomicIntegerArrayTest::equals(JObject* reached, JObject* expected){
                    JAtomicIntegerArray* r=dynamic_cast<JAtomicIntegerArray*>(reached);
                    JAtomicIntegerArray* e=dynamic_cast<JAtomicIntegerArray*>(expected);
                    assertEquals(r->get(0),e->get(0));
                }

                JObject* JAtomicIntegerArrayTest::getSerializableObject(){
                    JAtomicIntegerArray* a1=new JAtomicIntegerArray(1);
                    a1->set(0,1978);
                    return a1;
                }

                JAtomicIntegerArrayTest::~JAtomicIntegerArrayTest(){
                }
            }
        }
    }
}
