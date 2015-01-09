#include "org/w3c/dom/JDOMError.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace w3c{
        namespace dom{

            jshort JDOMError::SEVERITY_WARNING = 1;

            jshort JDOMError::SEVERITY_ERROR = 2;

            jshort JDOMError::SEVERITY_FATAL_ERROR = 3;

            JDOMError::~JDOMError(){
            }
        }
    }
}
