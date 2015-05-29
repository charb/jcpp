#ifndef JCPP_LANG_INFO_JOBJECTINFOGROUPVISITORRESULTTEST_H_
#define JCPP_LANG_INFO_JOBJECTINFOGROUPVISITORRESULTTEST_H_

#include "jcpp/lang/JString.h"
#include "jcpp/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::io;
using namespace junit::framework;
using namespace jcpp::lang;
using namespace jcpp;


namespace jcpp{
    namespace lang{
        namespace info{

           	//@Class(canonicalName="jcpp.lang.info.ObjectInfoGroupVisitorResultTest", simpleName="ObjectInfoGroupVisitorResultTest");
            class JCPP_EXPORT JObjectInfoGroupVisitorResultTest : public JTestCase{
            public:
            	JObjectInfoGroupVisitorResultTest();

                static JClass* getClazz();


                virtual void test();


                virtual ~JObjectInfoGroupVisitorResultTest();
            };
        }
    }
}

#endif
