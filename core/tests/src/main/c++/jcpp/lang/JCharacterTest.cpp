#include "jcpp/lang/JCharacterTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JCharacterTest::JCharacterTest():JSerializableTest(getClazz()){
        }

        JObject* JCharacterTest::getSerializableObject(){
            JPrimitiveObjectArray* a=new JPrimitiveObjectArray(JCharacter::getClazz(),3);
            a->set(0,new JCharacter((jchar)'c'));
            a->set(1,new JCharacter(JCharacter::MAX_VALUE));
            a->set(2,new JCharacter(JCharacter::MIN_VALUE));
            return a;
        }

        JCharacterTest::~JCharacterTest(){
        }
    }
}
