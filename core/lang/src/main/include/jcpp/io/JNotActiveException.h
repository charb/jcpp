#ifndef JCPP_IO_JNOTACTIVEEXCEPTION_H
#define JCPP_IO_JNOTACTIVEEXCEPTION_H

#include "jcpp/io/JObjectStreamException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp {
	namespace io {

		//@Class(canonicalName="java.io.NotActiveException", simpleName="NotActiveException");
		class JCPP_EXPORT JNotActiveException: public JObjectStreamException {
		private:
			static const jlong serialVersionUID = 3893467273049808895LL;
		protected:
			JNotActiveException(jcpp::lang::JClass* _clazz);

		public:
			JNotActiveException();

			JNotActiveException(JString* message);

			static jcpp::lang::JClass* getClazz();

			virtual ~JNotActiveException();
		};
	}
}

#endif
