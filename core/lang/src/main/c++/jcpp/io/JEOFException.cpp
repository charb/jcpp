#include "jcpp/io/JEOFException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JEOFException::JEOFException():JIOException(getClazz()){
        }

        JEOFException::JEOFException(JString* message) : JIOException(getClazz()){
            this->detailMessage=message;
        }

        JEOFException::~JEOFException(){
        }
    }
}
