#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/JUtilTestSuite.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JConcurrentModificationExceptionTest.h"
#include "jcpp/util/JNoSuchElementExceptionTest.h"
#include "jcpp/util/JArrayListTest.h"
#include "jcpp/util/JVectorTest.h"
#include "jcpp/util/JHashMapTest.h"
#include "jcpp/util/JHashMapAPITest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{


        JUtilTestSuite::JUtilTestSuite():JTestSuite(JUtilTestSuite::getClazz(),true){
            addTest(new JConcurrentModificationExceptionTest());
            addTest(new JNoSuchElementExceptionTest());
            addTest(new JArrayListTest());
            addTest(new JVectorTest());
            addTest(new JHashMapTest());
            addTest(new JHashMapAPITest());
        }

        JUtilTestSuite::~JUtilTestSuite(){
        }
    }
}
