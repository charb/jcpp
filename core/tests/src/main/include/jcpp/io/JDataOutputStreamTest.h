#ifndef JCPP_IO_JDATAOUTPUTSTREAM_TEST_H
#define JCPP_IO_JDATAOUTPUTSTREAM_TEST_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JDataInputStream.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/JAbstractTest.h"

using namespace junit::framework;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="jcpp.io.DataOutputStreamTest", simpleName="DataOutputStreamTest");
        class JCPP_EXPORT JDataOutputStreamTest : public JAbstractTest{
        protected:
        	JDataInputStream* in;
            JDataOutputStream* out;
            JFile* outputFile;
            JDataInputStream* newIn;
            virtual void test(JDataInputStream* in);
            virtual void writeTo();

        public:
            JDataOutputStreamTest(JString* name);

            static JClass* getClazz();

            virtual void setUp();
        	
        	virtual void tearDown();

            virtual void test();

            virtual ~JDataOutputStreamTest();
        };
    }
}
#endif
