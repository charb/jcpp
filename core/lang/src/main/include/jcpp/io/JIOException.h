#ifndef JCPP_IO_JIOEXCEPTION_H
#define JCPP_IO_JIOEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp {
	namespace io {

		//@Class(canonicalName="java.io.IOException", simpleName="IOException");
		class JCPP_EXPORT JIOException: public JException {
		private:
			static const jlong serialVersionUID = 7818375828146090155LL;
		protected:
			JIOException(jcpp::lang::JClass* _class);

		public:
			JIOException();

			JIOException(jcpp::lang::JString* message);

			static jcpp::lang::JClass* getClazz();

			virtual ~JIOException();
		};
	}
}

#endif
