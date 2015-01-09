#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/concurrent/atomic/JAtomicTestSuite.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicBooleanTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicIntegerArrayTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicIntegerTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicLongArrayTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicLongTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicReferenceArrayTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicReferenceTest.h"
#include "jcpp/util/concurrent/atomic/JAtomicsTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{


                JAtomicTestSuite::JAtomicTestSuite():JTestSuite(JAtomicTestSuite::getClazz(),true){
                    addTest(new JAtomicBooleanTest());
                    addTest(new JAtomicIntegerArrayTest());
                    addTest(new JAtomicIntegerTest());
                    addTest(new JAtomicLongArrayTest());
                    addTest(new JAtomicLongTest());
                    addTest(new JAtomicReferenceArrayTest());
                    addTest(new JAtomicReferenceTest());
                    addTest(new JAtomicsTest());
                }

                JAtomicTestSuite::~JAtomicTestSuite(){
                }
            }
        }
    }
}
