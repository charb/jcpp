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
#include "jcpp/util/JArrays.h"

using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JPrimitiveTest::JPrimitiveTest():JSerializableTest(getClazz()){
        }

        void JPrimitiveTest::equals(JObject* reached, JObject* expected){
            JPrimitiveObjectArray* a1=dynamic_cast<JPrimitiveObjectArray*>(reached);
            JPrimitiveObjectArray* a2=dynamic_cast<JPrimitiveObjectArray*>(expected);

            JPrimitiveBooleanArray* b1=dynamic_cast<JPrimitiveBooleanArray*>(a1->get(0));
            JPrimitiveBooleanArray* b2=dynamic_cast<JPrimitiveBooleanArray*>(a2->get(0));
            assertTrue(new JString("Asserting that 2 boolean arrays are equals"),JArrays::equals(b1,b2));

            JPrimitiveByteArray* by1=dynamic_cast<JPrimitiveByteArray*>(a1->get(1));
            JPrimitiveByteArray* by2=dynamic_cast<JPrimitiveByteArray*>(a2->get(1));
            assertTrue(new JString("Asserting that 2 byte arrays are equals"),JArrays::equals(by1,by2));

            JPrimitiveCharArray* cs1=dynamic_cast<JPrimitiveCharArray*>(a1->get(2));
            JPrimitiveCharArray* cs2=dynamic_cast<JPrimitiveCharArray*>(a2->get(2));
            assertTrue(new JString("Asserting that 2 char arrays are equals"),JArrays::equals(cs1,cs2));

            JPrimitiveDoubleArray* ds1=dynamic_cast<JPrimitiveDoubleArray*>(a1->get(3));
            JPrimitiveDoubleArray* ds2=dynamic_cast<JPrimitiveDoubleArray*>(a2->get(3));
            assertTrue(new JString("Asserting that 2 double arrays are equals"),JArrays::equals(ds1,ds2));

            JPrimitiveFloatArray* fs1=dynamic_cast<JPrimitiveFloatArray*>(a1->get(4));
            JPrimitiveFloatArray* fs2=dynamic_cast<JPrimitiveFloatArray*>(a2->get(4));
            assertTrue(new JString("Asserting that 2 float arrays are equals"),JArrays::equals(fs1,fs2));

            JPrimitiveIntArray* is1=dynamic_cast<JPrimitiveIntArray*>(a1->get(5));
            JPrimitiveIntArray* is2=dynamic_cast<JPrimitiveIntArray*>(a2->get(5));
            assertTrue(new JString("Asserting that 2 int arrays are equals"),JArrays::equals(is1,is2));

            JPrimitiveLongArray* ls1=dynamic_cast<JPrimitiveLongArray*>(a1->get(6));
            JPrimitiveLongArray* ls2=dynamic_cast<JPrimitiveLongArray*>(a2->get(6));
            assertTrue(new JString("Asserting that 2 long arrays are equals"),JArrays::equals(ls1,ls2));

            JPrimitiveShortArray* ss1=dynamic_cast<JPrimitiveShortArray*>(a1->get(7));
            JPrimitiveShortArray* ss2=dynamic_cast<JPrimitiveShortArray*>(a2->get(7));
            assertTrue(new JString("Asserting that 2 short arrays are equals"),JArrays::equals(ss1,ss2));
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
