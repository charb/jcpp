#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/xml/parsers/JAbstractTest.h"

using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace parsers{


            JAbstractTest::JAbstractTest(JClass* _class,JString* name):JTestCase(_class,name){
            }

            JAbstractTest::~JAbstractTest(){
            }
        }
    }
}
