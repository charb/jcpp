#include "jcpp/util/concurrent/atomic/JAtomicReferenceArrayTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicReferenceArray.h"
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

                JAtomicReferenceArrayTest::JAtomicReferenceArrayTest():JSerializableTest(getClazz()){
                }

                void JAtomicReferenceArrayTest::equals(JObject* reached, JObject* expected){
                    JAtomicReferenceArray* r=dynamic_cast<JAtomicReferenceArray*>(reached);
                    JAtomicReferenceArray* e=dynamic_cast<JAtomicReferenceArray*>(expected);
                    assertEquals(r->get(0),e->get(0));
                }

                JObject* JAtomicReferenceArrayTest::getSerializableObject(){
                    JAtomicReferenceArray* a1=new JAtomicReferenceArray(1);
                    a1->set(0,new JLong(1978));
                    return a1;
                }

                JAtomicReferenceArrayTest::~JAtomicReferenceArrayTest(){
                }
            }
        }
    }
}
