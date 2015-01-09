#ifndef JCPP_IO_JOBJECTOUTPUTSTREAM_TEST_H
#define JCPP_IO_JOBJECTOUTPUTSTREAM_TEST_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/JAbstractTest.h"

using namespace junit::framework;

namespace jcpp{
    namespace io{

       	//@Class(canonicalName="jcpp.io.ObjectOutputStreamTest", simpleName="ObjectOutputStreamTest");
        class JCPP_EXPORT JObjectOutputStreamTest : public JAbstractTest{
        protected:
        	JObjectInputStream* in;
            JObjectOutputStream* out;
            JFile* outputFile;
            JObjectInputStream* newIn;
            virtual void test(JObjectInputStream* in);
            virtual void writeTo();

        public:
            JObjectOutputStreamTest(JString* name);

            static JClass* getClazz();

            virtual void setUp();
        	
        	virtual void tearDown();

            virtual void test();

            virtual ~JObjectOutputStreamTest();
        };
    }
}
#endif
