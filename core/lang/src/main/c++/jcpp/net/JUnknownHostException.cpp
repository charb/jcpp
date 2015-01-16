#include "jcpp/net/JUnknownHostException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{

        JUnknownHostException::JUnknownHostException():JIOException(getClazz()){
        }

        JUnknownHostException::JUnknownHostException(JString* message) : JIOException(getClazz()){
            this->detailMessage=message;
        }

        JUnknownHostException::~JUnknownHostException(){
        }
    }
}
