#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/outlook/tests/JOutlookTestSuite.h"
#include "jcpp/outlook/tests/JOutlookTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace outlook{
        namespace tests{

            JOutlookTestSuite::JOutlookTestSuite():JTestSuite(JOutlookTestSuite::getClazz(),true){
                addTest(new JOutlookTest());
            }

            JOutlookTestSuite* JOutlookTestSuite::suite(){
                return new JOutlookTestSuite();
            }

            JOutlookTestSuite::~JOutlookTestSuite(){
            }
        }
    }
}
