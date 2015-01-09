#ifndef JCPP_IO_JUNSUPPORTEDENCODINGEXCEPTION_H
#define JCPP_IO_JUNSUPPORTEDENCODINGEXCEPTION_H

#include "jcpp/io/JIOException.h"

namespace jcpp {
	namespace io {
		//@Class(canonicalName="java.io.UnsupportedEncodingException", simpleName="UnsupportedEncodingException");
		class JCPP_EXPORT JUnsupportedEncodingException: public JIOException {
		private:
			static const jlong serialVersionUID = -4274276298326136670LL;
		public:
			static jcpp::lang::JClass* getClazz();

			JUnsupportedEncodingException();

			JUnsupportedEncodingException(JString* m);

			virtual ~JUnsupportedEncodingException();
		};
	}
}

#endif
