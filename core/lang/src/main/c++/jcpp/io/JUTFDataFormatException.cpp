#include "jcpp/io/JUTFDataFormatException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JUTFDataFormatException::JUTFDataFormatException():JIOException(getClazz()){
        }

        JUTFDataFormatException::JUTFDataFormatException(JString* message) : JIOException(getClazz()){
            this->detailMessage=message;
        }

        JUTFDataFormatException::~JUTFDataFormatException(){
        }
    }
}
