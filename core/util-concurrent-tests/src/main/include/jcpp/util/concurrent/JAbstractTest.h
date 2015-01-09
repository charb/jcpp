#ifndef JCPP_UTIL_CONCURRENT_ABSTRACT_TEST_H
#define JCPP_UTIL_CONCURRENT_ABSTRACT_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JFile.h"
#include "junit/framework/JTestSuite.h"
#include "junit/framework/JTestCase.h"

using namespace junit::framework;

namespace jcpp{
	namespace util{
		namespace concurrent{

			// @Class(canonicalName="jcpp.util.concurrent.AbstractTest", simpleName="AbstractTest");
		    class JCPP_EXPORT JAbstractTest : public JTestCase{
		    protected:
		    	JFile* createOutputFile(JClass* c);
		    	JFile* createOutputFile(JClass* c,JString* name);
		        JAbstractTest(JClass* _class,JString* name);

		    public:

		        static JClass* getClazz();

		        virtual ~JAbstractTest();
		    };
		}
	}
}
#endif
