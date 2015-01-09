#include "jcpp/util/concurrent/atomic/JAtomicReferenceTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicReference.h"
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

                JAtomicReferenceTest::JAtomicReferenceTest():JSerializableTest(getClazz()){
                }

                void JAtomicReferenceTest::equals(JObject* reached, JObject* expected){
                    JAtomicReference* r=dynamic_cast<JAtomicReference*>(reached);
                    JAtomicReference* e=dynamic_cast<JAtomicReference*>(expected);
                    assertEquals(r->get(),e->get());
                }

                JObject* JAtomicReferenceTest::getSerializableObject(){
                    JAtomicReference* a1=new JAtomicReference(new JLong(1978));
                    return a1;
                }

                JAtomicReferenceTest::~JAtomicReferenceTest(){
                }
            }
        }
    }
}
