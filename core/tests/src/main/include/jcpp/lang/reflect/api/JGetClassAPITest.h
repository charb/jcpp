/*
 * JMyTest.h
 *
 *  Created on: Nov 7, 2014
 *      Author: zrenno
 */

#ifndef JGET_CLASS_API_TEST_H_
#define JGET_CLASS_API_TEST_H_

#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/reflect/api/JClassC.h"
#include "jcpp/lang/reflect/api/JClassB.h"
#include "jcpp/lang/reflect/api/JInterfaceA.h"
#include "jcpp/lang/reflect/api/JInterfaceB.h"
#include "jcpp/lang/reflect/api/JInterfaceC.h"
#include "jcpp/lang/reflect/api/JInterfaceD.h"


namespace jcpp {
	namespace lang {
		namespace reflect{
			namespace api{

using namespace junit::framework;

//@Class(canonicalName="cpp.lang.reflect.api.GetClassAPITest", simpleName="GetClassAPITest");
				class JCPP_EXPORT JGetClassAPITest : public JAbstractTest{
				public:
					JGetClassAPITest(JString* name);
					JGetClassAPITest();
					virtual ~JGetClassAPITest();

					virtual void test();

					virtual void setUp();

					virtual void tearDown();

					static JClass* getClazz();

				};

			} /* namespace io */
		} /* namespace jcpp */
	}
}
#endif /* JMYTEST_H_ */
