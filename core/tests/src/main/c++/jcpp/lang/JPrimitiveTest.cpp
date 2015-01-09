#include "jcpp/lang/JPrimitiveTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveDoubleArray.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveShortArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JPrimitiveTest::JPrimitiveTest():JSerializableTest(getClazz()){
        }

        JObject* JPrimitiveTest::getSerializableObject(){
            JPrimitiveBooleanArray* b=new JPrimitiveBooleanArray(2);
            b->setBoolean(0,true);
            b->setBoolean(1,false);

            JPrimitiveByteArray* by=new JPrimitiveByteArray(2);
            by->setByte(0,78);
            by->setByte(1,79);

            JPrimitiveCharArray* cs=new JPrimitiveCharArray(2);
            cs->setChar(0,'c');
            cs->setChar(1,'d');

            JPrimitiveDoubleArray* ds=new JPrimitiveDoubleArray(2);
            ds->setDouble(0,78);
            ds->setDouble(1,79);

            JPrimitiveFloatArray* fs=new JPrimitiveFloatArray(2);
            fs->setFloat(0,78);
            fs->setFloat(1,79);

            JPrimitiveIntArray* is=new JPrimitiveIntArray(2);
            is->setInt(0,78);
            is->setInt(1,79);

            JPrimitiveLongArray* ls=new JPrimitiveLongArray(2);
            ls->setLong(0,78);
            ls->setLong(1,79);

            JPrimitiveShortArray* ss=new JPrimitiveShortArray(2);
            ss->setShort(0,78);
            ss->setShort(1,79);

            JPrimitiveObjectArray* oos=new JPrimitiveObjectArray(JObject::getClazz(), 8);
            oos->set(0,b);
            oos->set(1,by);
            oos->set(2,cs);
            oos->set(3,ds);
            oos->set(4,fs);
            oos->set(5,is);
            oos->set(6,ls);
            oos->set(7,ss);

            return oos;
        }

        JPrimitiveTest::~JPrimitiveTest(){
        }
    }
}
