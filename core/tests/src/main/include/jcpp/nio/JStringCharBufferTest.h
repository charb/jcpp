/*
 * JStringCharBufferTest.h
 *
 *  Created on: Jan 7, 2015
 *      Author: wkhalil
 */

#ifndef JCPP_NIO_JSTRINGCHARBUFFER_TEST_H_
#define JCPP_NIO_JSTRINGCHARBUFFER_TEST_H_


#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/lang/JString.h"

using namespace junit::framework;
namespace jcpp {
	namespace nio {

		//@Class(canonicalName="jcpp.nio.StringCharBufferTest", simpleName="StringCharBufferTest");
		 class JCPP_EXPORT JStringCharBufferTest : public JTestCase {
		 public:
			 JStringCharBufferTest();

			 static JClass* getClazz();

			 virtual void test();

			 virtual ~JStringCharBufferTest();

		 };
	}
}




#endif /* JCPP_NIO_JSTRINGCHARBUFFER_TEST_H_ */
