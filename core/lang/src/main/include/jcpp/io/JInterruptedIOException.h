#ifndef JCPP_IO_JINTERRUPTEDIOEXCEPTION_H
#define JCPP_IO_JINTERRUPTEDIOEXCEPTION_H

#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JPrimitiveInt.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace io {

		//@Class(canonicalName="java.io.InterruptedIOException", simpleName="InterruptedIOException");
		class JCPP_EXPORT JInterruptedIOException: public JIOException {
		private:
			static const jlong serialVersionUID = 4020568460727500567LL;
		protected:
			JPrimitiveInt* bytesTransferred;

		public:
			static jcpp::lang::JClass* getClazz();

			JInterruptedIOException();

			JInterruptedIOException(JString* message);

			jint getBytesTransferred();

			void setBytesTransferred(jint bt);

			virtual ~JInterruptedIOException();
		};
	}
}

#endif
