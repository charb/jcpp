#include "jcpp/nio/JNIOTestSuite.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/nio/JStringEncodingTest.h"
#include "jcpp/nio/JStringDecodingEncodingTest.h"
#include "jcpp/nio/JHeapByteBufferTest.h"
#include "jcpp/nio/JHeapCharBufferTest.h"
#include "jcpp/nio/JStringCharBufferTest.h"

using namespace jcpp::nio;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace nio {

	JNIOTestSuite::JNIOTestSuite() : JTestSuite(JNIOTestSuite::getClazz(), true)
	{
		addTest(new JStringEncodingTest(new JString("test")));
		addTest(new JStringDecodingEncodingTest());
		addTest(new JHeapByteBufferTest());
		addTest(new JHeapCharBufferTest());
		addTest(new JStringCharBufferTest());
	}

	JNIOTestSuite::~JNIOTestSuite()
	{	}



	}
}

