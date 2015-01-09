#include "jcpp/io/JIOException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

    	JIOException::JIOException():JException(getClazz()){
        }

        JIOException::JIOException(jcpp::lang::JClass* _class):JException(_class){
        }

        JIOException::JIOException(JString* message) : JException(getClazz()){
            this->message=message;
        }

        JIOException::~JIOException(){
        }
    }
}
