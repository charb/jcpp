#ifndef JCPP_UTIL_CONCURRENT_JSERIALIZABLE_TEST_H
#define JCPP_UTIL_CONCURRENT_JSERIALIZABLE_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/util/concurrent/JAbstractTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace junit::framework;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="jcpp.util.concurrent.SerializableTest", simpleName="SerializableTest");
            class JCPP_EXPORT JSerializableTest : public JAbstractTest{
            protected:
            	JObjectInputStream* in;
                JObjectOutputStream* out;
                JFile* outputFile;
                JObjectInputStream* newIn;
                virtual void test(JObjectInputStream* in);
                virtual void writeTo();
                JSerializableTest(JClass* _class);

            public:

                static JClass* getClazz();

                virtual void equals(JObject* reached, JObject* expected);

                virtual JObject* getSerializableObject()=0;

                virtual void setUp();
            	
            	virtual void tearDown();

                virtual void test();

                virtual ~JSerializableTest();
            };
        }
    }
}
#endif
