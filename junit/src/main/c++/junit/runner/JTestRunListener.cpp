#include "junit/runner/JTestRunListener.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"

namespace junit{
    namespace runner{

        jint JTestRunListener::STATUS_ERROR = 1;
                
        jint JTestRunListener::STATUS_FAILURE = 2;

        JTestRunListener::~JTestRunListener(){
        }
    }
}

