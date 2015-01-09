#include "jcpp/io/JCharConversionException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

    	JCharConversionException::JCharConversionException():JIOException(getClazz()){
        }

        JCharConversionException::JCharConversionException(JString* message):JIOException(getClazz()){
            setMessage(message);
        }

        JCharConversionException::~JCharConversionException(){
        }
    }
}
