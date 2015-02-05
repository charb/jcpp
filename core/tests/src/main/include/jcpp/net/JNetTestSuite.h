#ifndef JCPP_NET_TEST_SUITE_H_
#define JCPP_NET_TEST_SUITE_H_


#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
  namespace net{
      //@Class(canonicalName="jcpp.net.NetTestSuite", simpleName="NetTestSuite");
      class JCPP_EXPORT JNetTestSuite : public JTestSuite{
      public:
          JNetTestSuite();

          static JClass* getClazz();

          virtual ~JNetTestSuite();
      };
  }
}


#endif /* JCPP_NET_TEST_SUITE_H_ */
