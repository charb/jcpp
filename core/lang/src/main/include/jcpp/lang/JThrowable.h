#ifndef JCPP_LANG_JTHROWABLE_H
#define JCPP_LANG_JTHROWABLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStackTraceElement.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JList.h"
#include "jcpp/native/api/NativeException.h"

using namespace jcpp::native::api;
using namespace jcpp::util;

#define TRY_CATCH_NATIVE_EXCEPTION(CODE) 		\
	try { 										\
		CODE									\
	} catch (NativeException& e) {				\
		JThrowable::throwJException(e);	\
	}


namespace jcpp{
    namespace io{
        class JPrintStream;
        class JPrintWriter;
        class JFileOutputStream;
        class JFileInputStream;
        class JNativeOutputStream;
        class JNativeInputStream;
        class JFile;
    }

    namespace net{
    	class JInetAddress;
    	class JSocket;
    	class JServerSocket;
    }

    namespace lang{
    	class JProcess;
    	class JProcessBuilder;
    	class JThrowableClass;

        class JCPP_EXPORT JThrowable: public JObject, public JSerializable {
        protected:
            JString* message;
            JThrowable* cause;
            JPrimitiveObjectArray* stackTrace;
            JList* suppressedExceptions;
            JThrowable(jcpp::lang::JClass* _class);
            friend class JThrowableClass;

            static void throwJException(const NativeException& e);

        public:
            JThrowable();

            JThrowable(JString* message);

            JThrowable(JString* message, JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual void setCause(JThrowable* throwable);

            virtual JThrowable *getCause();

            virtual void setMessage(JString* message);

            virtual JString* getMessage();

            virtual void setStackTrace(JPrimitiveObjectArray* stackTrace);

            virtual JPrimitiveObjectArray* getStackTrace();

            virtual JList* getSuppressedExceptions();

            virtual void addSuppressedException(JThrowable* t);

            virtual void printStackTrace(JPrintStream* ps);

            virtual void printStackTrace(JPrintWriter* ps);

            virtual void printStackTrace();

            virtual jbool equals(JObject* other);

            virtual JString* toString();

            virtual ~JThrowable();

            friend class jcpp::io::JFileOutputStream;
            friend class jcpp::io::JFileInputStream;
            friend class jcpp::io::JNativeOutputStream;
            friend class jcpp::io::JNativeInputStream;
			friend class jcpp::io::JFile;
			friend class JObject;
			friend class jcpp::lang::JProcess;
			friend class jcpp::lang::JProcessBuilder;
			friend class jcpp::net::JInetAddress;
			friend class jcpp::net::JSocket;
			friend class jcpp::net::JServerSocket;
        };
    }
}

#endif
