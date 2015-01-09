#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_INTEGER_TEST_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_INTEGER_TEST_H

#include "jcpp/lang/JString.h"
#include "jcpp/util/concurrent/JSerializableTest.h"
#include "junit/framework/JTestCase.h"
#include "junit/framework/JTestSuite.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

using namespace jcpp::io;
using namespace jcpp;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="jcpp.util.concurrent.atomic.AtomicIntegerTest", simpleName="AtomicIntegerTest");
                class JCPP_EXPORT JAtomicIntegerTest : public JSerializableTest{
                public:
                    JAtomicIntegerTest();

                    static JClass* getClazz();

                    virtual void equals(JObject* reached, JObject* expected);

                    virtual JObject* getSerializableObject();

                    virtual ~JAtomicIntegerTest();
                };
            }
        }
    }
}
#endif
