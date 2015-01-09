#ifndef JCPP_IO_JFILEOUTPUTSTREAM_TEST_H
#define JCPP_IO_JFILEOUTPUTSTREAM_TEST_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/JAbstractTest.h"

using namespace junit::framework;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="jcpp.io.FileOutputStreamTest", simpleName="FileOutputStreamTest");
        class JCPP_EXPORT JFileOutputStreamTest : public JAbstractTest{
        protected:
        	JFileInputStream* in;
            JFileOutputStream* out;
            JFile* outputFile;
            JFileInputStream* newIn;
            virtual void test(JFileInputStream* in);
            virtual void writeTo();

        public:
            JFileOutputStreamTest(JString* name);

            static JClass* getClazz();

            virtual void setUp();
        	
        	virtual void tearDown();

            virtual void test();

            virtual ~JFileOutputStreamTest();
        };
    }
}
#endif
