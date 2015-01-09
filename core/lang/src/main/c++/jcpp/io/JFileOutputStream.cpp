#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JFileNotFoundException.h"
#include "jcpp/native/api/NativeFactory.h"

using jcpp::native::api::NativeFactory;

namespace jcpp{
    namespace io{

        JFileOutputStream::JFileOutputStream(JString* name,jbool append):JOutputStream(getClazz()){
            if (name == null) {
                throw new JNullPointerException();
            }
            closeLock=new JObject();
            bIsClosed=false;            
            TRY_CATCH_NATIVE_EXCEPTION( nativeStream = NativeFactory::getNativeIOFactory()->createFileOutputStream(name->getNativeString(), append); )
        }

        JFileOutputStream::JFileOutputStream(JFile* file,jbool append):JOutputStream(getClazz()){
            closeLock=new JObject();
            bIsClosed=false;
            JString* name = (file != null ? file->getPath() : null);
            if (name == null) {
                throw new JNullPointerException();
            }
            TRY_CATCH_NATIVE_EXCEPTION( nativeStream = NativeFactory::getNativeIOFactory()->createFileOutputStream(name->getNativeString(), append); )
        }

        void JFileOutputStream::write(jint b){
        	TRY_CATCH_NATIVE_EXCEPTION( nativeStream->write(b & 0x000000FF); )
        }

        void JFileOutputStream::write(JPrimitiveByteArray* b){
            write(b,0,b->size());
        }

        void JFileOutputStream::write(JPrimitiveByteArray* b,jint off,jint len){
        	TRY_CATCH_NATIVE_EXCEPTION( nativeStream->write(b->getArray(), off, len); )
        }

        void JFileOutputStream::close(){
            synchronized (closeLock,{
                if (bIsClosed) {
                    return;
                }
                TRY_CATCH_NATIVE_EXCEPTION( nativeStream->close(); )
                bIsClosed = true;
            })
        }

        void JFileOutputStream::finalize(){
            close();
            if(nativeStream) {
            	TRY_CATCH_NATIVE_EXCEPTION( delete nativeStream; )
				nativeStream = null;
            }
        }

        JFileOutputStream::~JFileOutputStream(){
        }
    }
}

