#include "jcpp/io/JFileNotFoundException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JFileNotFoundException::JFileNotFoundException():JIOException(getClazz()){
        }

        JFileNotFoundException::JFileNotFoundException(JString* m):JIOException(getClazz()){
            setMessage(m);
        }

        JFileNotFoundException::~JFileNotFoundException(){
        }
    }
}
