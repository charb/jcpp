#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/JConcurrentTestSuite.h"
#include "jcpp/util/concurrent/locks/JLocksTestSuite.h"
#include "jcpp/util/concurrent/atomic/JAtomicTestSuite.h"
#include "jcpp/util/concurrent/JBrokenBarrierExceptionTest.h"
#include "jcpp/util/concurrent/JCancellationExceptionTest.h"
#include "jcpp/util/concurrent/JCompletionExceptionTest.h"
#include "jcpp/util/concurrent/JExecutionExceptionTest.h"
#include "jcpp/util/concurrent/JExecutorServiceTest.h"
#include "jcpp/util/concurrent/JRejectedExecutionExceptionTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;
using namespace jcpp::util::concurrent::atomic;
using namespace jcpp::util::concurrent::locks;

namespace jcpp{
    namespace util{
        namespace concurrent{


            JConcurrentTestSuite::JConcurrentTestSuite():JTestSuite(JConcurrentTestSuite::getClazz(),true){
                addTest(new JBrokenBarrierExceptionTest());
                addTest(new JCancellationExceptionTest());
                //activate when using jdk8 : addTest(new JCompletionExceptionTest());
                addTest(new JExecutionExceptionTest());
                addTest(new JExecutorServiceTest());
                addTest(new JRejectedExecutionExceptionTest());
                addTest(new JAtomicTestSuite());
                addTest(new JLocksTestSuite());
            }

            JConcurrentTestSuite* JConcurrentTestSuite::suite(){
                return new JConcurrentTestSuite();
            }

            JConcurrentTestSuite::~JConcurrentTestSuite(){
            }
        }
    }
}
