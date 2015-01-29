/*
 * JClassTest.h
 *
 *  Created on: Nov 7, 2014
 *      Author: zrenno
 */

#ifndef JMCLASSTEST_H_
#define JMCLASSTEST_H_

#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/reflect/api/JClassC.h"
#include "jcpp/lang/reflect/api/JClassB.h"
#include "jcpp/lang/reflect/api/JInterfaceA.h"
#include "jcpp/lang/reflect/api/JInterfaceB.h"
#include "jcpp/lang/reflect/api/JInterfaceC.h"
#include "jcpp/lang/reflect/api/JInterfaceD.h"


namespace jcpp {
	namespace lang{
		namespace reflect{
			namespace api{

using namespace junit::framework;

//@Class(canonicalName="jcpp.io.MClassTest", simpleName="MClassTest");
class JCPP_EXPORT JClassAPITest : public JAbstractTest{
protected:
	void testFindDeclaredConstructor(JList* parameterTypes, JConstructor* rightAnswer);
	void testFindConstructor(JList* parameterTypes, JConstructor* rightAnswer);
	void testFindDeclaredMethod(JString* name, JList* parameterTypes, JMethod* rightAnswer);
	void testFindMethod(JString* name, JList* parameterTypes, JMethod* rightAnswer);
	void testFindDeclaredField(JString* name, JField* rightAnswer);
	void testFindField(JString* name, JField* rightAnswer);
	JConstructor* constructorInListWithParameterTypes(JList* params, JList* constructors);
	JMember* memberInListNamed(JString* name, JList* members);
	void logit(JClass* claz);
	void logit(JList* list);
	void logit(JMember* member);
public:
	JClassAPITest(JString* name);
	JClassAPITest();
	virtual ~JClassAPITest();

	virtual void test();

    virtual void setUp();

	virtual void tearDown();

	static JClass* getClazz();

};

} /* namespace io */
} /* namespace jcpp */
}
}
#endif /* JCLASSTEST_H_ */
