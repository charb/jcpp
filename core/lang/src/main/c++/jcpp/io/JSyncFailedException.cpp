#include "jcpp/io/JSyncFailedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JSyncFailedException::JSyncFailedException():JIOException(getClazz()){
        }

        JSyncFailedException::JSyncFailedException(JString* message):JIOException(getClazz()){
            this->message=message;
        }

        JSyncFailedException::~JSyncFailedException(){
        }
    }
}
