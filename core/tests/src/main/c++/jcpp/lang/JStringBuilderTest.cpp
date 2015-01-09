#include "jcpp/lang/JStringBuilderTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStringBuilderTest::JStringBuilderTest():JSerializableTest(getClazz()){
        }

        JObject* JStringBuilderTest::getSerializableObject(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(new JString("This is a test"));
            return builder;
        }

        JStringBuilderTest::~JStringBuilderTest(){
        }
    }
}
