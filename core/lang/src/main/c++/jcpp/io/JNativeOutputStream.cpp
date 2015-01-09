#include "jcpp/io/JNativeOutputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JNativeOutputStream::JNativeOutputStream(NativeOutputStream* stream, jbool deleteNativeStreamAtFinalize):JOutputStream(getClazz()){
        	this->stream=stream;
        	this->deleteNativeStreamAtFinalize = deleteNativeStreamAtFinalize;
        }

        void JNativeOutputStream::write(jint b) {
        	TRY_CATCH_NATIVE_EXCEPTION( stream->write(b & 0x000000FF); )
        }

        void JNativeOutputStream::write(JPrimitiveByteArray* b) {
        	TRY_CATCH_NATIVE_EXCEPTION( write(b, 0, b->size()); )
        }

        void JNativeOutputStream::write(JPrimitiveByteArray* b, jint off, jint len) {
        	TRY_CATCH_NATIVE_EXCEPTION( stream->write(b->getArray(), off, len); )
        }

        void JNativeOutputStream::flush() {
        	TRY_CATCH_NATIVE_EXCEPTION( stream->flush(); )
        }

        void JNativeOutputStream::close() {
        	TRY_CATCH_NATIVE_EXCEPTION( stream->close(); )
        }

        void JNativeOutputStream::finalize() {
        	if(deleteNativeStreamAtFinalize && stream) {
        		delete stream;
        		stream = null;
        	}
        }

        JNativeOutputStream::~JNativeOutputStream(){
        }
    }
}
