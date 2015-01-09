#include "jcpp/util/concurrent/atomic/JAtomicIntegerTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
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

                JAtomicIntegerTest::JAtomicIntegerTest():JSerializableTest(getClazz()){
                }

                void JAtomicIntegerTest::equals(JObject* reached, JObject* expected){
                    JAtomicInteger* r=dynamic_cast<JAtomicInteger*>(reached);
                    JAtomicInteger* e=dynamic_cast<JAtomicInteger*>(expected);
                    assertEquals(r->get(),e->get());
                }

                JObject* JAtomicIntegerTest::getSerializableObject(){
                    JAtomicInteger* a1=new JAtomicInteger();
                    a1->set(1978);
                    return a1;
                }

                JAtomicIntegerTest::~JAtomicIntegerTest(){
                }
            }
        }
    }
}
