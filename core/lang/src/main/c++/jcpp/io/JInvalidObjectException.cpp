#include "jcpp/io/JInvalidObjectException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JInvalidObjectException::JInvalidObjectException():JObjectStreamException(getClazz()){
        }

        JInvalidObjectException::JInvalidObjectException(JString* message) : JObjectStreamException(getClazz()){
            this->message=message;
        }

        JInvalidObjectException::~JInvalidObjectException(){
        }
    }
}

