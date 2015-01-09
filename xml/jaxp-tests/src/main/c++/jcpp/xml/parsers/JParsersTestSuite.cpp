#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/xml/parsers/JParsersTestSuite.h"
#include "jcpp/xml/parsers/JParsersTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace xml{
        namespace parsers{


            JParsersTestSuite::JParsersTestSuite():JTestSuite(JParsersTestSuite::getClazz(),true){
                addTest(new JParsersTest());
            }

            JParsersTestSuite* JParsersTestSuite::suite(){
                return new JParsersTestSuite();
            }

            JParsersTestSuite::~JParsersTestSuite(){
            }
        }
    }
}
