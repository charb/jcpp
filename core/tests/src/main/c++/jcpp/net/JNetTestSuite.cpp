#include "jcpp/net/JNetTestSuite.h"
#include "jcpp/net/JSocketTest.h"
#include "jcpp/net/JSocketExceptionTest.h"
#include "jcpp/net/JSocketTimeoutExceptionTest.h"
using namespace jcpp::net;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{

        JNetTestSuite::JNetTestSuite():JTestSuite(JNetTestSuite::getClazz(),true){
        	addTest(new JSocketTest());
        	addTest(new JSocketExceptionTest());
        	addTest(new JSocketTimeoutExceptionTest());
        }

        JNetTestSuite::~JNetTestSuite(){
        }
    }
}
