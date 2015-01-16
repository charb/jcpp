#include "junit/framework/JComparisonFailure.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JAssertionError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace junit{
    namespace framework{

        JComparisonFailure::JComparisonFailure():JAssertionFailedError(getClazz()){
            this->detailMessage=null;
            this->fExpected=null;
            this->fActual=null;
        }

        JComparisonFailure::JComparisonFailure(JString* message, JString* expected, JString* actual):JAssertionFailedError(getClazz()){
            this->detailMessage=message;
            this->fExpected=expected;
            this->fActual=actual;
        }

        JString* JComparisonFailure::getActual(){
            return fActual;
        }

        JString* JComparisonFailure::getExpected(){
            return fExpected;
        }

        JComparisonFailure::~JComparisonFailure(){
        }
    }
}

