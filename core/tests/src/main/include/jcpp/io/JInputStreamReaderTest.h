#ifndef JCPP_IO_JINPUTSTREAMREADER_TEST_H
#define JCPP_IO_JINPUTSTREAMREADER_TEST_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JInputStreamReader.h"
#include "jcpp/io/JInputStream.h"

using namespace junit::framework;
using namespace jcpp::lang;
using namespace jcpp;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="jcpp.io.InputStreamReaderTest", simpleName="InputStreamReaderTest");
        class JCPP_EXPORT JInputStreamReaderTest : public JTestCase {
        public:
            JInputStreamReaderTest();

            static JClass* getClazz();

            void test();

            virtual ~JInputStreamReaderTest();
        };
    }
}
#endif
