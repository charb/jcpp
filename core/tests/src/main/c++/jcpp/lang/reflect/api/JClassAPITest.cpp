/*
 * JMClassTest.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: zrenno
 */

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/JPrimitiveFloat.h"

#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/api/JClassAPITest.h"
#include "jcpp/lang/reflect/api/JInterfaceC.h"
#include "jcpp/lang/reflect/api/JInterfaceD.h"
#include "jcpp/lang/reflect/api/JClassC.h"

namespace jcpp {
	namespace lang {
		namespace reflect{
			namespace api {

JClassAPITest::JClassAPITest(JString* name) :JAbstractTest(getClazz(),name){
	// TODO Auto-generated constructor stub

}
JClassAPITest::JClassAPITest() :JAbstractTest(getClazz(),new JString("test")){
	// TODO Auto-generated constructor stub

}


JClassAPITest::~JClassAPITest() {
	// TODO Auto-generated destructor stub
}


void logit(JMember* member){
	JStringBuilder *stb = new JStringBuilder();
	stb->append(member->getName());
	stb->append(new JString(" From "));
	stb->append(member->getDeclaringClass()->getName());
	JSystem::out->println(stb->toString());
}

void logit(JList* list){
	JIterator *i = list->iterator();
	while (i->hasNext())
		logit(dynamic_cast<JMember*>(i->next()));
}

void logit(JClass* claz)
{
	JSystem::out->println(claz->getName());

	JSystem::out->println(new JString("----------Fields----------"));
	JList* fields = claz->getFields();
	logit(fields);

	JSystem::out->println(new JString("----------Declared Fields----------"));
	fields = claz->getDeclaredFields();
	logit(fields);


	JSystem::out->println(new JString("---------Methods---------"));
	logit(claz->getMethods());

	JSystem::out->println(new JString("---------Declared Methods---------"));
	logit(claz->getDeclaredMethods());

	JSystem::out->println(new JString("---------Constructors---------"));
	logit(claz->getConstructors());

	JSystem::out->println(new JString("---------Declared Constructors---------"));
	logit(claz->getDeclaredConstructors());

}

JMember* memberInListNamed(JString* name, JList* members){
	JIterator* i = members->iterator();
	while (i->hasNext()){
		JMember* member = dynamic_cast<JMember*>(i->next());
		if (member->getName()->equals(name))
			return member;
	}
	return null;
}

JConstructor* constructorInListWithParameterTypes(JList* params, JList* constructors){
	JIterator* i = constructors->iterator();
	while (i->hasNext()){
		JConstructor* constructor = dynamic_cast<JConstructor*>(i->next());
		if (constructor->getParameterTypes()->equals(dynamic_cast<JObject*>(params)))
			return constructor;
	}
	return null;
}

void testFindField(JString* name, JField* rightAnswer){
	try {
		JField* res = JClassC::getClazz()->getField(name);
		if (rightAnswer == null)
			JClassAPITest::assertFalse(true);
		else
			JClassAPITest::assertEquals(dynamic_cast<JObject*>(res), dynamic_cast<JObject*>(rightAnswer));
	}catch (JObject* obj){
		if (rightAnswer == null)
			JClassAPITest::assertEquals(obj->getClass(), JNoSuchFieldException::getClazz());
		else
			JClassAPITest::assertFalse(true);
	}
}
void testFindDeclaredField(JString* name, JField* rightAnswer){
	try {
		JField* res = JClassC::getClazz()->getDeclaredField(name);
		if (rightAnswer == null)
			JClassAPITest::assertFalse(true);
		else
			JClassAPITest::assertEquals(dynamic_cast<JObject*>(res), dynamic_cast<JObject*>(rightAnswer));
	}catch (JObject* obj){
		if (rightAnswer == null)
			JClassAPITest::assertEquals(obj->getClass(), JNoSuchFieldException::getClazz());
		else
			JClassAPITest::assertFalse(true);
	}
}

void testFindMethod(JString* name, JList* parameterTypes, JMethod* rightAnswer){
	try{
		JMethod* res = JClassC::getClazz()->getMethod(name, parameterTypes);
		if (rightAnswer == null){
			JClassAPITest::assertFalse(true);
		}
		else{
			JClassAPITest::assertEquals(dynamic_cast<JObject*>(res), dynamic_cast<JObject*>(rightAnswer));
		}
	}catch (JObject* obj){
		if (rightAnswer==null){
			JClassAPITest::assertEquals(obj->getClass(), JNoSuchMethodException::getClazz());
		}
		else{
			JClassAPITest::assertFalse(true);
		}
	}
}
void testFindDeclaredMethod(JString* name, JList* parameterTypes, JMethod* rightAnswer){
	try{
		JMethod* res = JClassC::getClazz()->getDeclaredMethod(name, parameterTypes);
		if (rightAnswer == null){
			JClassAPITest::assertFalse(true);
		}
		else{
			JClassAPITest::assertEquals(dynamic_cast<JObject*>(res), dynamic_cast<JObject*>(rightAnswer));
		}
	}catch (JObject* obj){
		if (rightAnswer==null){
			JClassAPITest::assertEquals(obj->getClass(), JNoSuchMethodException::getClazz());
		}
		else{
			JClassAPITest::assertFalse(true);
		}
	}
}

void testFindConstructor(JList* parameterTypes, JConstructor* rightAnswer){
	try{
		JConstructor* res = JClassC::getClazz()->getConstructor(parameterTypes);
		if (rightAnswer == null){
			JClassAPITest::assertFalse(true);
		}
		else{
			JClassAPITest::assertEquals(dynamic_cast<JObject*>(res), dynamic_cast<JObject*>(rightAnswer));
		}
	}catch (JObject* obj){
		if (rightAnswer==null){
			JClassAPITest::assertEquals(obj->getClass(), JNoSuchMethodException::getClazz());
		}
		else{
			JClassAPITest::assertFalse(true);
		}
	}
}
void testFindDeclaredConstructor(JList* parameterTypes, JConstructor* rightAnswer){
	try{
		JConstructor* res = JClassC::getClazz()->getDeclaredConstructor(parameterTypes);
		if (rightAnswer == null){
			JClassAPITest::assertFalse(true);
		}
		else{
			JClassAPITest::assertEquals(dynamic_cast<JObject*>(res), dynamic_cast<JObject*>(rightAnswer));
		}
	}catch (JObject* obj){
		if (rightAnswer==null){
			JClassAPITest::assertEquals(obj->getClass(), JNoSuchMethodException::getClazz());
		}
		else{
			JClassAPITest::assertFalse(true);
		}
	}
}

void JClassAPITest::test(){

	JSystem::out->println(new JString("-------------initiating test--------"));

	logit(JInterfaceD::getClazz());
	logit(JInterfaceC::getClazz());

	logit(JClassB::getClazz());
	logit(JClassC::getClazz());

	JClassC::getClazz()->getField(new JString("publicFieldZ"));



	JSystem::out->println(new JString("-------------1 down--------"));


	JList* classCFields = JClassC::getClazz()->getFields();
	JList* classCDeclaredFields = JClassC::getClazz()->getDeclaredFields();
	JList* classCMethods = JClassC::getClazz()->getMethods();
	JList* classCDeclaredMethods = JClassC::getClazz()->getDeclaredMethods();
	JList* classCConstructors = JClassC::getClazz()->getConstructors();
	JList* classCDeclaredConstructors = JClassC::getClazz()->getDeclaredConstructors();

	JList* parameterTypes = new JArrayList();
	JSystem::out->println(new JString("//test normal public constructors"));
	parameterTypes->clear();
	assertNotNull(dynamic_cast<JObject*>(constructorInListWithParameterTypes(parameterTypes, classCConstructors))); JSystem::out->println(new JString("//default constructor"));

	JSystem::out->println(new JString("//test non leakage of private constructor"));
	parameterTypes->clear();
	parameterTypes->add(jcpp::lang::JPrimitiveFloat::getClazz());
	parameterTypes->add(jcpp::lang::JPrimitiveFloat::getClazz());
	assertNull(dynamic_cast<JObject*>(constructorInListWithParameterTypes(parameterTypes, classCConstructors)));
	testFindConstructor(parameterTypes, dynamic_cast<JConstructor*>(constructorInListWithParameterTypes(parameterTypes, classCConstructors)));

	JSystem::out->println(new JString("//test non leakage of protected constructor"));
	parameterTypes->clear();
	parameterTypes->add(jcpp::lang::JPrimitiveInt::getClazz());
	parameterTypes->add(jcpp::lang::JPrimitiveInt::getClazz());
	assertNull(dynamic_cast<JObject*>(constructorInListWithParameterTypes(parameterTypes, classCConstructors)));
	testFindConstructor(parameterTypes, null);


	JSystem::out->println(new JString("//test normal public constructors"));
	parameterTypes->clear();
	assertNotNull(dynamic_cast<JObject*>(constructorInListWithParameterTypes(parameterTypes, classCDeclaredConstructors))); JSystem::out->println(new JString("//default constructor"));
	JSystem::out->println(new JString("//test find constr"));
	testFindDeclaredConstructor(parameterTypes, dynamic_cast<JConstructor*>(constructorInListWithParameterTypes(parameterTypes, classCDeclaredConstructors)));

	JSystem::out->println(new JString("//test private constructor"));
	parameterTypes->clear();
	parameterTypes->add(jcpp::lang::JPrimitiveFloat::getClazz());
	parameterTypes->add(jcpp::lang::JPrimitiveFloat::getClazz());
	assertNotNull(dynamic_cast<JObject*>(constructorInListWithParameterTypes(parameterTypes, classCDeclaredConstructors)));
	testFindDeclaredConstructor(parameterTypes, dynamic_cast<JConstructor*>(constructorInListWithParameterTypes(parameterTypes, classCDeclaredConstructors)));

	JSystem::out->println(new JString("//test protected constructor"));
	parameterTypes->clear();
	parameterTypes->add(jcpp::lang::JPrimitiveInt::getClazz());
	parameterTypes->add(jcpp::lang::JPrimitiveInt::getClazz());
	assertNotNull(dynamic_cast<JObject*>(constructorInListWithParameterTypes(parameterTypes, classCDeclaredConstructors)));
	testFindDeclaredConstructor(parameterTypes, dynamic_cast<JConstructor*>(constructorInListWithParameterTypes(parameterTypes, classCDeclaredConstructors)));

	JSystem::out->println(new JString("//test normal public field"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicFieldZ"), classCFields)));
	JSystem::out->println(new JString("//test search public field"));
	testFindField(new JString("publicFieldZ"), dynamic_cast<JField*>(memberInListNamed(new JString("publicFieldZ"), classCFields)));

	JSystem::out->println(new JString("//test non leakage of private/protected fields"));
	assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("privateField"), classCFields)));
	assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("protectedField"), classCFields)));
	JSystem::out->println(new JString("//test search not found on private member"));
	testFindField(new JString("privateField"), null);
	JSystem::out->println(new JString("//test search not found on protected member"));
	testFindField(new JString("protectedField"), null);

	JSystem::out->println(new JString("//test order of interface fields"));
	JMember* m1 = memberInListNamed(new JString("publicIntFieldC"), classCFields);
	assertNotNull(dynamic_cast<JObject*>(m1));
	assertEquals(m1->getDeclaringClass(), JInterfaceD::getClazz());

	JSystem::out->println(new JString("//test search for interface field"));
	testFindField(new JString("publicIntFieldC"), dynamic_cast<JField*>(memberInListNamed(new JString("publicIntFieldC"), classCFields)));

	JSystem::out->println(new JString("//test deep interface field"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicIntFieldA"), classCFields)));

	JSystem::out->println(new JString("//test field from parent"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicFieldB"), classCFields)));

	JSystem::out->println(new JString("//test fields with same name. Attention to order"));
	JIterator* it = classCFields->iterator();
	int counter = 0;
	while (it->hasNext()){
		JField* field = dynamic_cast<JField*>(it->next());
		if (field->getName()->equals(new JString("publicFieldB"))){
			++counter;
			switch (counter){
			case 1:
				assertEquals(JClassC::getClazz(), field->getDeclaringClass());
				break;
			case 2:
				assertEquals(JInterfaceB::getClazz(), field->getDeclaringClass());
				break;
			case 3:
				assertEquals(JClassB::getClazz(), field->getDeclaringClass());
				break;
			}
		}
	}
	assertEquals(counter, 3);

	JSystem::out->println(new JString("//test normal public field"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicFieldZ"), classCDeclaredFields)));
	JSystem::out->println(new JString("//test search declared fields"));
	testFindDeclaredField(new JString("publicFieldZ"), dynamic_cast<JField*>(memberInListNamed(new JString("publicFieldZ"), classCDeclaredFields)));

	JSystem::out->println(new JString("//test normal private field"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("privateField"), classCDeclaredFields)));
	JSystem::out->println(new JString("//test search private"));
	testFindDeclaredField(new JString("privateField"), dynamic_cast<JField*>(memberInListNamed(new JString("privateField"), classCDeclaredFields)));

	JSystem::out->println(new JString("//test normal protected field"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("protectedField"), classCDeclaredFields)));
	JSystem::out->println(new JString("//test search protected"));
	testFindDeclaredField(new JString("protectedField"), dynamic_cast<JField*>(memberInListNamed(new JString("protectedField"), classCDeclaredFields)));

	JSystem::out->println(new JString("//test non leakage from interfaces"));
	assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicIntFieldC"), classCDeclaredFields)));
	JSystem::out->println(new JString("//non leakage find"));
	testFindDeclaredField(new JString("publicIntFieldC"), null);

	JSystem::out->println(new JString("//test non leakage from parent"));
	assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicField"), classCDeclaredFields)));
	testFindDeclaredField(new JString("publicField"), null);

	JSystem::out->println(new JString("//test standard method"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicMethod"), classCMethods)));
	JList* methParams = new JArrayList();
	JSystem::out->println(new JString("//test find public method"));
	methParams->clear();
	testFindMethod(new JString("publicMethod"), null, dynamic_cast<JMethod*>(memberInListNamed(new JString("publicMethod"), classCMethods)));
	testFindMethod(new JString("publicMethod"), methParams, dynamic_cast<JMethod*>(memberInListNamed(new JString("publicMethod"), classCMethods)));
	JSystem::out->println(new JString("//test wrong params"));
	methParams->add(JPrimitiveFloat::getClazz());
	testFindMethod(new JString("publicMethod"), methParams, null);

	JSystem::out->println(new JString("//test polymorphism"));
	JMember* meth2 = memberInListNamed(new JString("methodPoly"), classCMethods);
	assertNotNull(dynamic_cast<JObject*>(meth2));
	assertEquals(meth2->getDeclaringClass(), JClassC::getClazz());

	JSystem::out->println(new JString("//test find polymorphism"));
	methParams->clear();
	testFindMethod(new JString("methodPoly"), null, dynamic_cast<JMethod*>(memberInListNamed(new JString("methodPoly"), classCMethods)));

	//test non leakage of private/protected methods
	//TODO uncomment once method visibility has been sorted
	//assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("privateMethod"), classCMethods)));
	//assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("protectedMethod"), classCMethods)));

	JSystem::out->println(new JString("//test methods from interfaces"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicMethodFromC"), classCMethods)));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicMethodFromD"), classCMethods)));
	JSystem::out->println(new JString("//test find from interface"));
	methParams->clear();
	testFindMethod(new JString("publicMethodFromC"), methParams, dynamic_cast<JMethod*>(memberInListNamed(new JString("publicMethodFromC"), classCMethods)));


	JSystem::out->println(new JString("//test methods from parent"));
	JMember* meth1 = memberInListNamed(new JString("methodBBB"), classCMethods);
	assertNotNull(dynamic_cast<JObject*>(meth1));
	assertEquals(meth1->getDeclaringClass(), JClassB::getClazz());
	JSystem::out->println(new JString("//test find from parent"));
	methParams->clear();
	testFindMethod(new JString("methodBBB"), methParams, dynamic_cast<JMethod*>(memberInListNamed(new JString("methodBBB"), classCMethods)));

	JSystem::out->println(new JString("//test public method"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicMethod"), classCDeclaredMethods)));
	testFindDeclaredMethod(new JString("publicMethod"), null, dynamic_cast<JMethod*>(memberInListNamed(new JString("publicMethod"), classCDeclaredMethods)));
	methParams->clear();
	testFindDeclaredMethod(new JString("publicMethod"), methParams, dynamic_cast<JMethod*>(memberInListNamed(new JString("publicMethod"), classCDeclaredMethods)));
	methParams->add(JPrimitiveFloat::getClazz());
	testFindDeclaredMethod(new JString("publicMethod"), methParams, null);

	JSystem::out->println(new JString("//test private method"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("privateMethod"), classCDeclaredMethods)));
	methParams->clear();
	testFindDeclaredMethod(new JString("privateMethod"), methParams, dynamic_cast<JMethod*>(memberInListNamed(new JString("privateMethod"), classCDeclaredMethods)));


	JSystem::out->println(new JString("//test protected declared method"));
	assertNotNull(dynamic_cast<JObject*>(memberInListNamed(new JString("protectedMethod"), classCDeclaredMethods)));

	JSystem::out->println(new JString("//test non leakage of declared methods from interfaces"));
	assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("publicMethodFromC"), classCDeclaredMethods)));
	methParams->clear();
	testFindDeclaredMethod(new JString("publicMethodFromC"), methParams, null);

	JSystem::out->println(new JString("//test non leakage of declared methods from parents"));
	assertNull(dynamic_cast<JObject*>(memberInListNamed(new JString("methodBBB"), classCDeclaredMethods)));
	methParams->clear();
	testFindDeclaredMethod(new JString("methodBBB"), methParams, null);

}

void JClassAPITest::setUp(){}
void JClassAPITest::tearDown(){}

} /* namespace io */
} /* namespace jcpp */
}
}
