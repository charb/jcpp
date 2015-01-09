#include "jcpp/util/concurrent/atomic/JAtomicLongTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicLong.h"
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

                JAtomicLongTest::JAtomicLongTest():JSerializableTest(getClazz()){
                }

                void JAtomicLongTest::equals(JObject* reached, JObject* expected){
                    JAtomicLong* r=dynamic_cast<JAtomicLong*>(reached);
                    JAtomicLong* e=dynamic_cast<JAtomicLong*>(expected);
                    assertEquals(r->get(),e->get());
                }

                JObject* JAtomicLongTest::getSerializableObject(){
                    JAtomicLong* a1=new JAtomicLong();
                    a1->set(1978);
                    return a1;
                }

                JAtomicLongTest::~JAtomicLongTest(){
                }
            }
        }
    }
}
