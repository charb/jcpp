#include "jcpp/io/JFileInputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JFileNotFoundException.h"
#include "jcpp/io/JFile.h"
#include "jcpp/native/api/NativeFactory.h"

using jcpp::native::api::NativeFactory;

namespace jcpp{
    namespace io{

        JFileInputStream::JFileInputStream(JString* name):JInputStream(getClazz()){
            if (name == null) {
                throw new JNullPointerException();
            }
            bIsClosed=false;
            closeLock=new JObject();
            TRY_CATCH_NATIVE_EXCEPTION( nativeStream = NativeFactory::getNativeIOFactory()->createFileInputStream(name->getNativeString()); )
        }

        JFileInputStream::JFileInputStream(JFile* file):JInputStream(getClazz()){
            bIsClosed=false;
            closeLock=new JObject();
            JString* name = (file != null ? file->getPath() : null);
            if (name == null) {
                throw new JNullPointerException();
            }
            TRY_CATCH_NATIVE_EXCEPTION( nativeStream = NativeFactory::getNativeIOFactory()->createFileInputStream(name->getNativeString()); )
        }

        jint JFileInputStream::read() {
        	jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeStream->read(); )
			return value & 0xFF;
        }

        jint JFileInputStream::read(JPrimitiveByteArray* b){
            return read(b,0,b->size());
        }

        jint JFileInputStream::read(JPrimitiveByteArray* b,jint off,jint len){
        	jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeStream->read(b->getArray(), off, len); )
			return value;
        }

        jlong JFileInputStream::skip(jlong n){
        	jlong value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeStream->skip(n); )
			return value;
        }

        jint JFileInputStream::available(){
            jint value = 0;
            TRY_CATCH_NATIVE_EXCEPTION( value = nativeStream->available(); )
            return value;
        }

        void JFileInputStream::close(){
            synchronized (closeLock,{
                if (bIsClosed) {
                    return;
                }
                TRY_CATCH_NATIVE_EXCEPTION( nativeStream->close(); )
                bIsClosed = true;
            })
        }

        void JFileInputStream::finalize(){
            close();
            if(nativeStream) {
				TRY_CATCH_NATIVE_EXCEPTION( delete nativeStream; )
				nativeStream = null;
			}
        }

        JFileInputStream::~JFileInputStream() {
        }
    }
}
