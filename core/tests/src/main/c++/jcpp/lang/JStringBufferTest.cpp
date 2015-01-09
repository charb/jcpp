#include "jcpp/lang/JStringBufferTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuffer.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStringBufferTest::JStringBufferTest():JSerializableTest(getClazz()){
        }

        JObject* JStringBufferTest::getSerializableObject(){
            JStringBuffer* builder=new JStringBuffer();
            builder->append(new JString("This is a test"));
            return builder;
        }

        JStringBufferTest::~JStringBufferTest(){
        }
    }
}
