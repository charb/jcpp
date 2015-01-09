#include "jcpp/io/JNotActiveException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{


        JNotActiveException::JNotActiveException(jcpp::lang::JClass* _class):JObjectStreamException(_class){
        }

        JNotActiveException::JNotActiveException():JObjectStreamException(getClazz()){
        }

        JNotActiveException::JNotActiveException(JString* message) : JObjectStreamException(getClazz()){
            this->message=message;
        }

        JNotActiveException::~JNotActiveException(){
        }
    }
}

