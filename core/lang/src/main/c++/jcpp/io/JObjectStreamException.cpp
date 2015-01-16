#include "jcpp/io/JObjectStreamException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JObjectStreamException::JObjectStreamException(jcpp::lang::JClass* _class):JIOException(_class){
        }

        JObjectStreamException::JObjectStreamException():JIOException(getClazz()){
        }

        JObjectStreamException::JObjectStreamException(JString* message) : JIOException(getClazz()){
            this->detailMessage=message;
        }

        JObjectStreamException::~JObjectStreamException(){
        }
    }
}
