#include "jcpp/io/JInvalidClassException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JInvalidClassException::JInvalidClassException():JObjectStreamException(getClazz()){
        }

        JInvalidClassException::JInvalidClassException(JString* message) : JObjectStreamException(getClazz()){
            this->message=message;
        }

        JInvalidClassException::JInvalidClassException(JString* classname,JString* message) : JObjectStreamException(getClazz()){
            this->classname=classname;
            this->message=message;
        }

        JString* JInvalidClassException::getClassname(){
            return classname;
        }

        JInvalidClassException::~JInvalidClassException(){
        }
    }
}
