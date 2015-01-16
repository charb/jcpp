#include "jcpp/io/JUnsupportedEncodingException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JUnsupportedEncodingException::JUnsupportedEncodingException():JIOException(getClazz()){
        }

        JUnsupportedEncodingException::JUnsupportedEncodingException(JString* m):JIOException(getClazz()){
            this->detailMessage=m;
        }

        JUnsupportedEncodingException::~JUnsupportedEncodingException(){
        }
    }
}
