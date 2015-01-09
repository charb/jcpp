/*
 * JMyTest.cpp
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

#include "jcpp/JCPPPackageLoader.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/api/JGetClassAPITest.h"
#include "jcpp/lang/reflect/api/JInterfaceC.h"
#include "jcpp/lang/reflect/api/JInterfaceD.h"


namespace jcpp {
	namespace lang {
		namespace reflect{
			namespace api{

JGetClassAPITest::JGetClassAPITest(JString* name) :JAbstractTest(getClazz(),name){
	// TODO Auto-generated constructor stub

}
JGetClassAPITest::JGetClassAPITest() :JAbstractTest(getClazz(),new JString("test")){
	// TODO Auto-generated constructor stub

}



JGetClassAPITest::~JGetClassAPITest() {
	// TODO Auto-generated destructor stub
}



void JGetClassAPITest::test(){
	JCPPPackageLoader *packageLoader = new JCPPPackageLoader();

	JList* packages = packageLoader->getPackage()->getPackages();
	JIterator* packagesIterator = packages->iterator();
	while (packagesIterator->hasNext()){
		JPackage *pack = (JPackage*)packagesIterator->next();
		JSystem::out->println(pack);

		JIterator *classesIterator = pack->getClasses()->iterator();
		while (classesIterator->hasNext()){
			JClass *classs = (JClass*)classesIterator->next();
			try{
				//JSystem::out->println(classs->getConstructors()->size());

				JConstructor *defaultConstructor = classs->getConstructor(null);
				JObject *obj = defaultConstructor->newInstance(null);


				JStringBuilder* sb = new JStringBuilder();
				sb->append("--> Created instance of: ")->append(obj->getClass()->getName());
				sb->append(" --> Hoping for instance of: ")->append(classs->getName());
				JSystem::out->println(sb->toString());

				assertEquals(classs, obj->getClass());

				//bool res = classs->equals(obj->getClass());
				//assertTrue(res);

			}catch (JNoSuchMethodException* exc){
				JSystem::out->println(new JString("--> No default constructor."));
			}
		}
	}
}

void JGetClassAPITest::setUp(){}
void JGetClassAPITest::tearDown(){}

} /* namespace io */
} /* namespace jcpp */
}
}
