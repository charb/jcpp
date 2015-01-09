#include "jcpp/lang/JEnumSampleObjectTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/JEnumSampleObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JEnumSampleObjectTest::JEnumSampleObjectTest():JSerializableTest(getClazz()){
        }

        void JEnumSampleObjectTest::equals(JObject* reached, JObject* expected){
            JSystem::out->println(new JString("========Reached=========="));
            JPrimitiveObjectArray* r=dynamic_cast<JPrimitiveObjectArray*>(reached);
            for (jint i=0;i<r->size();i++){
                JSystem::out->println(r->get(i));
            }
            JSystem::out->println(new JString("========================="));
            JSystem::out->println(new JString("========Expected========="));
            JPrimitiveObjectArray* e=dynamic_cast<JPrimitiveObjectArray*>(expected);
            for (jint i=0;i<e->size();i++){
                JSystem::out->println(e->get(i));
            }
            JSystem::out->println(new JString("========================="));
            assertEquals(reached,expected);
        }

        JObject* JEnumSampleObjectTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JEnumSampleObject::getClazz(),5);
            a->set(0,JEnumSampleObject::ENUM5);
            a->set(1,JEnumSampleObject::ENUM4);
            a->set(2,JEnumSampleObject::ENUM3);
            a->set(3,JEnumSampleObject::ENUM2);
            a->set(4,JEnumSampleObject::ENUM1);
            return a;
        }

        JEnumSampleObjectTest::~JEnumSampleObjectTest(){
        }
    }
}
