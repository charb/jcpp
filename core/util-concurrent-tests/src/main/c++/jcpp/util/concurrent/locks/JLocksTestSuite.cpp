#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/concurrent/locks/JLocksTestSuite.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/locks/JLocksTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

                JLocksTestSuite::JLocksTestSuite():JTestSuite(JLocksTestSuite::getClazz(),true){
                    addTest(new JLocksTest());
                }

                JLocksTestSuite::~JLocksTestSuite(){
                }
            }
        }
    }
}
