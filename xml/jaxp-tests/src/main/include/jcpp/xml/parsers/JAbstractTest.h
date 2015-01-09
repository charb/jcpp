#ifndef JCPP_XML_PARSERS_ABSTRACT_TEST_H
#define JCPP_XML_PARSERS_ABSTRACT_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JFile.h"
#include "junit/framework/JTestSuite.h"
#include "junit/framework/JTestCase.h"

using namespace junit::framework;

namespace jcpp{
	namespace xml{
		namespace parsers{
			//@Class(canonicalName="jcpp.xml.parsers.AbstractTest", simpleName="AbstractTest");
		    class JCPP_EXPORT JAbstractTest : public JTestCase{
		    protected:
		        JAbstractTest(JClass* _class,JString* name);

		    public:

		        static JClass* getClazz();

		        virtual ~JAbstractTest();
		    };
		}
	}
}
#endif
