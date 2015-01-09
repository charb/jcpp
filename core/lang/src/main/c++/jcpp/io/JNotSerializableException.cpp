#include "jcpp/io/JNotSerializableException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JNotSerializableException::JNotSerializableException(jcpp::lang::JClass* _class):JObjectStreamException(_class){
        }

        JNotSerializableException::JNotSerializableException():JObjectStreamException(getClazz()){
        }

        JNotSerializableException::JNotSerializableException(JString* message) : JObjectStreamException(getClazz()){
            this->message=message;
        }

        JNotSerializableException::~JNotSerializableException(){
        }
    }
}
