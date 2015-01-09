#include "jcpp/io/JNativeInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JNativeInputStream::JNativeInputStream(NativeInputStream* stream, jbool deleteNativeStreamAtFinalize):JInputStream(getClazz()){
        	this->stream=stream;
        	this->deleteNativeStreamAtFinalize = deleteNativeStreamAtFinalize;
        }

        jint JNativeInputStream::read(){
        	jint value = 0;
        	TRY_CATCH_NATIVE_EXCEPTION( value = stream->read(); )
            value=(jint)(value & 0xFF);
        	return value;
        }

        jint JNativeInputStream::read(JPrimitiveByteArray* b, jint off, jint len){
        	jint value = 0;
        	TRY_CATCH_NATIVE_EXCEPTION( value = stream->read(b->getArray(), off, len); )
        	return value;
        }

        jlong JNativeInputStream::skip(jlong n){
        	jlong value = 0;
        	TRY_CATCH_NATIVE_EXCEPTION( value = stream->skip(n); )
        	return value;
        }

        jint JNativeInputStream::available(){
        	jint value = 0;
        	TRY_CATCH_NATIVE_EXCEPTION( value = stream->available(); )
        	return value;
        }

        void JNativeInputStream::close(){
        	TRY_CATCH_NATIVE_EXCEPTION( stream->close(); )
        }

        void JNativeInputStream::finalize() {
        	if(deleteNativeStreamAtFinalize && stream) {
				delete stream;
				stream = null;
			}
        }

        JNativeInputStream::~JNativeInputStream(){
        }
    }
}
