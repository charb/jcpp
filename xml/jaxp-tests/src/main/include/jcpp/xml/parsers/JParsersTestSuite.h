#ifndef JCPP_XML_PARSERS_TEST_SUITE_H
#define JCPP_XML_PARSERS_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace xml{
		namespace parsers{

			// @Class(canonicalName="jcpp.xml.parsers.ParsersTestSuite", simpleName="ParsersTestSuite");
		    class JCPP_EXPORT JParsersTestSuite : public JTestSuite{
		    public:
		        JParsersTestSuite();

		        static JClass* getClazz();

		        static JParsersTestSuite* suite();

		        virtual ~JParsersTestSuite();
		    };
		}
	}
}
#endif
