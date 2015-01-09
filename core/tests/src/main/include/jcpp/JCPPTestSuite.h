#ifndef JCPP_TEST_SUITE_H
#define JCPP_TEST_SUITE_H

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{

    //@Class(canonicalName="jcpp.JCPPTestSuite", simpleName="JCPPTestSuite");
    class JCPP_EXPORT JCPPTestSuite : public JTestSuite{
    public:
        JCPPTestSuite();

        static JClass* getClazz();

        static JCPPTestSuite* suite();

        virtual ~JCPPTestSuite();
    };
}
#endif
