#include "jcpp/lang/JLangTestSuite.h"
#include "jcpp/io/JIOTestSuite.h"
#include "jcpp/nio/JNIOTestSuite.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/JCPPTestSuite.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JUtilTestSuite.h"
#include "jcpp/net/JNetTestSuite.h"
#include "jcpp/lang/info/JInfoTestSuite.h"


using namespace jcpp::io;
using namespace jcpp::nio;
using namespace jcpp::net;
using namespace jcpp::lang::info;
using namespace jcpp::lang::reflect;

namespace jcpp{

	JCPPTestSuite::JCPPTestSuite():JTestSuite(JCPPTestSuite::getClazz(),true){
        addTest(new JIOTestSuite());
        addTest(new JLangTestSuite());
        addTest(new JUtilTestSuite());
        addTest(new JNIOTestSuite());
        addTest(new JNetTestSuite());
		addTest(new JInfoTestSuite());
    }

    JCPPTestSuite* JCPPTestSuite::suite(){
        return new JCPPTestSuite();
    }

    JCPPTestSuite::~JCPPTestSuite(){
    }
}
