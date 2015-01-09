/*
 * JMHashMapTest.h
 *
 *  Created on: Nov 7, 2014
 *      Author: zrenno
 */

#ifndef JMHASHMAPTEST_H_
#define JMHASHMAPTEST_H_

#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/reflect/api/JClassC.h"
#include "jcpp/lang/reflect/api/JClassB.h"
#include "jcpp/lang/reflect/api/JInterfaceA.h"
#include "jcpp/lang/reflect/api/JInterfaceB.h"
#include "jcpp/lang/reflect/api/JInterfaceC.h"
#include "jcpp/lang/reflect/api/JInterfaceD.h"


namespace jcpp {
namespace util {

using namespace junit::framework;

//@Class(canonicalName="jcpp.io.MHashMapTest", simpleName="MHashMapTest");
class JCPP_EXPORT JHashMapAPITest : public JAbstractTest{
public:
	JHashMapAPITest(JString* name);
	JHashMapAPITest();
	virtual ~JHashMapAPITest();

	virtual void test();

    virtual void setUp();

	virtual void tearDown();

	static JClass* getClazz();

};

} /* namespace io */
} /* namespace jcpp */

#endif /* JMHashMapTest_H_ */
