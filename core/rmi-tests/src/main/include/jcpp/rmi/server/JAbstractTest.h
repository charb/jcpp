#ifndef JCPP_RMI_SERVER_ABSTRACT_TEST_H
#define JCPP_RMI_SERVER_ABSTRACT_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JFile.h"
#include "junit/framework/JTestSuite.h"
#include "junit/framework/JTestCase.h"

using namespace junit::framework;

namespace jcpp{
	namespace rmi{
		namespace server{

			// @Class(canonicalName="jcpp.rmi.server.AbstractTest", simpleName="AbstractTest");
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
