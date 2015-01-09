#include "jcpp/io/JObjectOutputStreamTest.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/JSampleObject.h"

using namespace jcpp;
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JObjectOutputStreamTest::JObjectOutputStreamTest(JString* name):JAbstractTest(getClazz(),name){
            in=null;
            out=null;
            newIn=null;
        }

        void JObjectOutputStreamTest::setUp(){
            JFile* file=createOutputFile(JObjectOutputStreamTest::getClazz());
            in=new JObjectInputStream(new JFileInputStream(file));

            outputFile=createOutputFile(JObjectOutputStreamTest::getClazz(),new JString("OutputTest"));
            out=new JObjectOutputStream(new JFileOutputStream(outputFile));
        }

        void JObjectOutputStreamTest::tearDown(){
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

        void JObjectOutputStreamTest::test(JObjectInputStream* in){
            for (jint i=0;i<11;i++){
                assertEquals(i,in->read());
            }

            JPrimitiveByteArray* b=new JPrimitiveByteArray(11);
            in->readFully(b);
            for (jint i=0;i<11;i++){
                assertEquals((jbyte)i,b->getByte(i));
            }

            assertEquals(true,in->readBoolean());
            assertEquals(false,in->readBoolean());

            b=new JPrimitiveByteArray(11);
            in->read(b);//Hello world

            //TEST
            assertEquals((jchar)'T',in->readChar());
            assertEquals((jchar)'E',in->readChar());
            assertEquals((jchar)'S',in->readChar());
            assertEquals((jchar)'T',in->readChar());

            //Hello world
            assertEquals((jchar)'H',in->readChar());
            assertEquals((jchar)'e',in->readChar());
            assertEquals((jchar)'l',in->readChar());
            assertEquals((jchar)'l',in->readChar());
            assertEquals((jchar)'o',in->readChar());
            assertEquals((jchar)' ',in->readChar());
            assertEquals((jchar)'w',in->readChar());
            assertEquals((jchar)'o',in->readChar());
            assertEquals((jchar)'r',in->readChar());
            assertEquals((jchar)'l',in->readChar());
            assertEquals((jchar)'d',in->readChar());

            assertEquals((jdouble)1978,in->readDouble(),0);

            assertEquals((jfloat)1978,in->readFloat(),0);

            assertEquals((jint)1978,in->readInt());

            assertEquals((jlong)1978,in->readLong());

            assertEquals((jshort)1978,in->readShort());

            JString* str=in->readUTF();//Hello world
            assertEquals(new JString("Hello world"),str);


            JSampleObject* so=dynamic_cast<JSampleObject*>(in->readObject());
            JSampleObject* ref=new JSampleObject(0,(jlong)1,(jshort)2,(jfloat)3,(jdouble)4,true,(jchar)'T',(jbyte)5);
            assertEquals(so,ref);
        }

        void JObjectOutputStreamTest::writeTo(){
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

            out->writeBoolean(true);
            out->writeBoolean(false);

            out->writeBytes(new JString("Hello world"));

            out->writeChar('T');
            out->writeChar('E');
            out->writeChar('S');
            out->writeChar('T');

            out->writeChars(new JString("Hello world"));

            out->writeDouble(1978);

            out->writeFloat(1978);

            out->writeInt(1978);

            out->writeLong(1978);

            out->writeShort(1978);

            out->writeUTF(new JString("Hello world"));

            JSampleObject* sampleObject=new JSampleObject(0,(jlong)1,(jshort)2,(jfloat)3,(jdouble)4,true,(jchar)'T',(jbyte)5);
            out->writeObject(sampleObject);

            out->flush();

            newIn=new JObjectInputStream(new JFileInputStream(outputFile));
        }

        void JObjectOutputStreamTest::test(){
            test(in);
            writeTo();
            test(newIn);
        }

        JObjectOutputStreamTest::~JObjectOutputStreamTest(){
        }
    }
}
