#ifndef JUNIT_FRAMEWORK_JTEST_SUITE_H
#define JUNIT_FRAMEWORK_JTEST_SUITE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "junit/framework/JTest.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JIterator.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace junit{
    namespace framework{
    	// @Class(canonicalName="junit.framework.TestSuite", simpleName="TestSuite");
        class JCPP_EXPORT JTestSuite : public JObject, public JTest{
        	protected:
        		JString* fName;
        		JList* fTests;

				static JString* exceptionToString(JThrowable* e);

        		JTestSuite(JClass* _class,jbool root);
				JTestSuite(JClass* _class,JClass* theClass,jbool root);
				JTestSuite(JClass* _class,JClass* theClass, JString* name,jbool root);
				JTestSuite(JClass* _class,JString* name,jbool root);
				JTestSuite(JClass* _class,JList* classes,jbool root);
				JTestSuite(JClass* _class,JList* classes, JString* name,jbool root);

        		virtual void addTestsFromTestCase(JClass* theClass);
        		virtual JTest* testCaseForClass(JClass* each);
        		virtual void addTestMethod(JMethod* m, JList* names, JClass* theClass);
        		virtual jbool isPublicTestMethod(JMethod* m);
				virtual jbool isTestMethod(JMethod* m);

            public:
				static JTest* createTest(JClass* theClass, JString* name);
				
				static JConstructor* getTestConstructor(JClass* theClass);

				static JTest* warning(JString* message);

				JTestSuite();

				JTestSuite(JClass* theClass);

				JTestSuite(JClass* theClass, JString* name);
				
				JTestSuite(JString* name);

				JTestSuite(JList* classes);

				JTestSuite(JList* classes, JString* name);

                static JClass* getClazz();

    			virtual void addTest(JTest* test);
				
				virtual void addTestSuite(JClass* testClass);

				virtual jint countTestCases();
				
				virtual JString* getName();

				virtual void run(JTestResult* result);

				virtual void runTest(JTest* test, JTestResult* result);
				
				virtual void setName(JString* name);

				virtual JTest* testAt(jint index);

				virtual jint testCount();

				virtual JIterator* tests();

				virtual JString* toString();
    
                virtual ~JTestSuite();
        };
    }
}
#endif
