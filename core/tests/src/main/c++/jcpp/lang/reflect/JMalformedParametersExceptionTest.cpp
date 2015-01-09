#include "jcpp/lang/reflect/JMalformedParametersExceptionTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JMalformedParametersException.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp {
	namespace lang {
		namespace reflect {

			JMalformedParametersExceptionTest::JMalformedParametersExceptionTest() :
					JSerializableTest(getClazz()) {
			}

			void JMalformedParametersExceptionTest::equals(JObject* reached, JObject* expected) {
				JMalformedParametersException* r = dynamic_cast<JMalformedParametersException*>(reached);
				r->printStackTrace();
				JMalformedParametersException* e = dynamic_cast<JMalformedParametersException*>(expected);
				assertEquals(r->getMessage(), e->getMessage());
				assertEquals(r->getCause()->getMessage(), e->getCause()->getMessage());
			}

			JObject* JMalformedParametersExceptionTest::getSerializableObject() {
				JMalformedParametersException* cause = new JMalformedParametersException(new JString("This is the cause"));
				JMalformedParametersException* exception = new JMalformedParametersException(new JString("The exception to test"));
				exception->setCause(cause);
				return exception;
			}

			JMalformedParametersExceptionTest::~JMalformedParametersExceptionTest() {
			}
		}
	}
}
