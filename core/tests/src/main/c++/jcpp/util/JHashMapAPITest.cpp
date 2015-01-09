/*
 * JMHashMapTest.cpp
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
#include "jcpp/util/JHashMap.h"

#include "jcpp/JCPPPackageLoader.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/util/JHashMapAPITest.h"

namespace jcpp {
namespace util {


JHashMapAPITest::JHashMapAPITest(JString* name) :JAbstractTest(getClazz(),name){
	// TODO Auto-generated constructor stub

}
JHashMapAPITest::JHashMapAPITest() :JAbstractTest(getClazz(),new JString("test")){
	// TODO Auto-generated constructor stub

}


JHashMapAPITest::~JHashMapAPITest() {
	// TODO Auto-generated destructor stub
}



void JHashMapAPITest::test(){
	JHashMap* map = new JHashMap();
	JPrimitiveFloat* key1 = new JPrimitiveFloat(1);
	assertFalse(map->containsKey(key1));
	JPrimitiveFloat* val1 = new JPrimitiveFloat(2);
	assertNull(map->put(key1, val1));
	assertTrue(map->containsKey(key1));
	JPrimitiveFloat* key2 = new JPrimitiveFloat(3);
	JPrimitiveFloat* val2 = new JPrimitiveFloat(4);
	assertEquals(map->put(key1, val2), val1);
	assertEquals(map->get(key1), val2);
	assertNull(map->get(key2));
	assertTrue(map->containsValue(val2));
	assertFalse(map->containsValue(val1));
	map->clear();
	assertTrue(map->isEmpty());
	assertFalse(map->containsKey(key1));
	map->put(key1, val1);
	assertEquals(map->remove(key1), val1);
	assertFalse(map->containsKey(key1));
	map->put(key1, val1);
	map->put(key2, val2);
	assertEquals(map->size(), new JPrimitiveInt(2));
	assertEquals(map->size(), map->entrySet()->size());
	JIterator* i = map->entrySet()->iterator();
	while (i->hasNext()){
		JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(i->next());
		assertTrue(map->values()->contains(entry->getValue()));
		assertTrue(map->keySet()->contains(entry->getKey()));
	}
	assertEquals(map, map->clone());
	JHashMap* map2 = new JHashMap();
	map2->putAll(map);
	assertEquals(map, map2);
}

void JHashMapAPITest::setUp(){}
void JHashMapAPITest::tearDown(){}

} /* namespace io */
} /* namespace jcpp */
