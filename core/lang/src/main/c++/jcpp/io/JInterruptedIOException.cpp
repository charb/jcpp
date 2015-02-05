#include "jcpp/io/JInterruptedIOException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JInterruptedIOException::JInterruptedIOException():JIOException(getClazz()){
            bytesTransferred=new JPrimitiveInt();
        }

        JInterruptedIOException::JInterruptedIOException(jcpp::lang::JClass* _class):JIOException(_class){
        	bytesTransferred=new JPrimitiveInt();
        }

        JInterruptedIOException::JInterruptedIOException(JString* m):JIOException(getClazz()){
            setMessage(m);
            bytesTransferred=new JPrimitiveInt();
        }

        jint JInterruptedIOException::getBytesTransferred(){
            return bytesTransferred->get();
        }

        void JInterruptedIOException::setBytesTransferred(jint bt){
            bytesTransferred->set(bt);
        }

        JInterruptedIOException::~JInterruptedIOException(){
        }
    }
}
