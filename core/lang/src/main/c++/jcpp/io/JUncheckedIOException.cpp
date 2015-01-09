#include "jcpp/io/JUncheckedIOException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JUncheckedIOException::JUncheckedIOException():JRuntimeException(getClazz()){
        }

        JUncheckedIOException::JUncheckedIOException(JString* m):JRuntimeException(getClazz()){
            this->message=m;
        }

        JUncheckedIOException::~JUncheckedIOException(){
        }
    }
}
