#include "jcpp/io/JStreamCorruptedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JStreamCorruptedException::JStreamCorruptedException(jcpp::lang::JClass* _class):JObjectStreamException(_class){
        }

        JStreamCorruptedException::JStreamCorruptedException():JObjectStreamException(getClazz()){
        }

        JStreamCorruptedException::JStreamCorruptedException(JString* message) : JObjectStreamException(getClazz()){
            this->detailMessage=message;
        }

        JStreamCorruptedException::~JStreamCorruptedException(){
        }
    }
}
