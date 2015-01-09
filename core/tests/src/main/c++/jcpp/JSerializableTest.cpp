#include "jcpp/JSerializableTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JException.h"
#include "jcpp/io/JObjectOutputStreamTest.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/io/JObjectInputStream.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{

    JSerializableTest::JSerializableTest(JClass* c):JAbstractTest(c,new JString("test")){
        in=null;
        out=null;
        newIn=null;
    }

    void JSerializableTest::equals(JObject* reached, JObject* expected){
        assertEquals(reached,expected);
    }

    void JSerializableTest::setUp(){
        JFile* file=createOutputFile(getClass());
        in=new JObjectInputStream(new JFileInputStream(file));
        
        outputFile=createOutputFile(getClass(),new JString("OutputTest"));
        out=new JObjectOutputStream(new JFileOutputStream(outputFile));
    }

    void JSerializableTest::tearDown(){
        if (in!=null){
            in->close();
        }
        if (out!=null){
            out->close();
        }
        if (newIn!=null){
            newIn->close();
        }
    }

    void JSerializableTest::test(JObjectInputStream* in){
        JObject* obj1=in->readObject();
        JObject* excpected=getSerializableObject();
        equals(obj1,excpected);
    }

    void JSerializableTest::writeTo(){
        JObject* excpected=getSerializableObject();
        out->writeObject(excpected);
        out->flush();

        newIn=new JObjectInputStream(new JFileInputStream(outputFile));
    }

    void JSerializableTest::test(){
        test(in);
        writeTo();
        test(newIn);
    }

    JSerializableTest::~JSerializableTest(){
    }
}
