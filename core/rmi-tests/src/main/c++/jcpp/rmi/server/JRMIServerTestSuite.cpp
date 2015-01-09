#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/rmi/server/JRMIServerTestSuite.h"
#include "jcpp/rmi/server/JRMIServerTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{

            JRMIServerTestSuite::JRMIServerTestSuite():JTestSuite(JRMIServerTestSuite::getClazz(),true){
                addTest(new JRMIServerTest());
            }

            JRMIServerTestSuite* JRMIServerTestSuite::suite(){
                return new JRMIServerTestSuite();
            }

            JRMIServerTestSuite::~JRMIServerTestSuite(){
            }
        }
    }
}
