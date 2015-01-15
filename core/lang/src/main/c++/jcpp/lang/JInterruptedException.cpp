#include "jcpp/lang/JInterruptedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInterruptedException::JInterruptedException():JException(getClazz()){
        }

        JInterruptedException::JInterruptedException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JInterruptedException::~JInterruptedException(){
        }
    }
}

