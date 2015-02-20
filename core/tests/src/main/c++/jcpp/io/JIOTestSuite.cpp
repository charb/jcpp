#include "jcpp/io/JFileOutputStreamTest.h"
#include "jcpp/io/JDataOutputStreamTest.h"
#include "jcpp/io/JObjectOutputStreamTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JIOTestSuite.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JCharConversionExceptionTest.h"
#include "jcpp/io/JEOFExceptionTest.h"
#include "jcpp/io/JFileNotFoundExceptionTest.h"
#include "jcpp/io/JInterruptedIOExceptionTest.h"
#include "jcpp/io/JInvalidClassExceptionTest.h"
#include "jcpp/io/JInvalidObjectExceptionTest.h"
#include "jcpp/io/JIOErrorTest.h"
#include "jcpp/io/JIOExceptionTest.h"
#include "jcpp/io/JNotActiveExceptionTest.h"
#include "jcpp/io/JNotSerializableExceptionTest.h"
#include "jcpp/io/JStreamCorruptedExceptionTest.h"
#include "jcpp/io/JSyncFailedExceptionTest.h"
#include "jcpp/io/JUncheckedIOExceptionTest.h"
#include "jcpp/io/JUnsupportedEncodingExceptionTest.h"
#include "jcpp/io/JUTFDataFormatExceptionTest.h"
#include "jcpp/io/JWriteAbortedExceptionTest.h"
#include "jcpp/io/JInputStreamReaderTest.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JIOTestSuite::JIOTestSuite():JTestSuite(JIOTestSuite::getClazz(),true){
            addTest(new JFileOutputStreamTest(new JString("test")));
            addTest(new JDataOutputStreamTest(new JString("test")));
            addTest(new JObjectOutputStreamTest(new JString("test")));
            addTest(new JCharConversionExceptionTest());
            addTest(new JEOFExceptionTest());
            addTest(new JFileNotFoundExceptionTest());
            addTest(new JInterruptedIOExceptionTest());
            addTest(new JInvalidClassExceptionTest());
            addTest(new JInvalidObjectExceptionTest());
            addTest(new JIOErrorTest());
            addTest(new JIOExceptionTest());
            addTest(new JNotActiveExceptionTest());
            addTest(new JNotSerializableExceptionTest());
            addTest(new JStreamCorruptedExceptionTest());
            addTest(new JSyncFailedExceptionTest());
            //addTest(new JUncheckedIOExceptionTest()); 		//TODO reactivate when on java8
            addTest(new JUnsupportedEncodingExceptionTest());
            addTest(new JUTFDataFormatExceptionTest());
            addTest(new JWriteAbortedExceptionTest());
            addTest(new JInputStreamReaderTest());
        }

        JIOTestSuite::~JIOTestSuite(){
        }
    }
}
