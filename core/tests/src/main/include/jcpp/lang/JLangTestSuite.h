#ifndef JCPP_LANG_TEST_SUITE_H
#define JCPP_LANG_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace lang{

	    //@Class(canonicalName="jcpp.lang.LangTestSuite", simpleName="LangTestSuite");
	    class JCPP_EXPORT JLangTestSuite : public JTestSuite{
	    public:
	        JLangTestSuite();

	        static JClass* getClazz();

	        virtual ~JLangTestSuite();
	    };
	}
}
#endif
