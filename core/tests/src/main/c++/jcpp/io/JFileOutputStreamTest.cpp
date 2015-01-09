#include "jcpp/io/JFileOutputStreamTest.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

      JFileOutputStreamTest::JFileOutputStreamTest(JString* name):JAbstractTest(getClazz(),name){
            in=null;
            out=null;
            newIn=null;
        }

        void JFileOutputStreamTest::setUp(){
            JFile* file=createOutputFile(JFileOutputStreamTest::getClazz());
            in=new JFileInputStream(file);

            outputFile=createOutputFile(JFileOutputStreamTest::getClazz(),new JString("OutputTest"));
            out=new JFileOutputStream(outputFile);
        }

        void JFileOutputStreamTest::tearDown(){
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

        void JFileOutputStreamTest::test(JFileInputStream* in){
            for (jint i=0;i<11;i++){
                assertEquals((jint)i,in->read());
            }
            JPrimitiveByteArray* b=new JPrimitiveByteArray(11);
            in->read(b);
            for (jint i=0;i<11;i++){
                assertEquals((jbyte)i,b->getByte(i));
            }
        }

        void JFileOutputStreamTest::writeTo(){
            out->write(0);
            out->write(1);
            out->write(2);
            out->write(3);
            out->write(4);
            out->write(5);
            out->write(6);
            out->write(7);
            out->write(8);
            out->write(9);
            out->write(10);
            
            JPrimitiveByteArray* b=new JPrimitiveByteArray(11);
            b->setByte(0,0);
            b->setByte(1,1);
            b->setByte(2,2);
            b->setByte(3,3);
            b->setByte(4,4);
            b->setByte(5,5);
            b->setByte(6,6);
            b->setByte(7,7);
            b->setByte(8,8);
            b->setByte(9,9);
            b->setByte(10,10);
            out->write(b);
            out->flush();
            newIn=new JFileInputStream(outputFile);
        }

        void JFileOutputStreamTest::test(){
            test(in);
            writeTo();
            test(newIn);
        }

        JFileOutputStreamTest::~JFileOutputStreamTest(){
        }
    }
}
