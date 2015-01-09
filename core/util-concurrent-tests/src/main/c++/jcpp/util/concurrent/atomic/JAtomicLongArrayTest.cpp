#include "jcpp/util/concurrent/atomic/JAtomicLongArrayTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicLongArray.h"
#include "jcpp/lang/JLong.h"
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

                JAtomicLongArrayTest::JAtomicLongArrayTest():JSerializableTest(getClazz()){
                }

                void JAtomicLongArrayTest::equals(JObject* reached, JObject* expected){
                    JAtomicLongArray* r=dynamic_cast<JAtomicLongArray*>(reached);
                    JAtomicLongArray* e=dynamic_cast<JAtomicLongArray*>(expected);
                    assertEquals(r->get(0),e->get(0));
                }

                JObject* JAtomicLongArrayTest::getSerializableObject(){
                    JAtomicLongArray* a1=new JAtomicLongArray(1);
                    a1->set(0,1978);
                    return a1;
                }

                JAtomicLongArrayTest::~JAtomicLongArrayTest(){
                }
            }
        }
    }
}
