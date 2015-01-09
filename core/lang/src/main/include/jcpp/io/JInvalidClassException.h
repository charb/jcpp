#ifndef JCPP_IO_JINVALIDCLASSEXCEPTION_H
#define JCPP_IO_JINVALIDCLASSEXCEPTION_H

#include "jcpp/io/JObjectStreamException.h"

namespace jcpp {
	namespace io {
		class JInvalidClassExceptionClass;
		//@Class(canonicalName="java.io.InvalidClassException", simpleName="InvalidClassException");
		class JCPP_EXPORT JInvalidClassException: public JObjectStreamException {
		private:
			static const jlong serialVersionUID = 4333316296251054416LL;
		protected:
			JString* classname;

		public:
			JInvalidClassException();

			JInvalidClassException(JString* message);

			JInvalidClassException(JString* classname, JString* message);

			static jcpp::lang::JClass* getClazz();

			virtual JString* getClassname();

			virtual ~JInvalidClassException();
		};
	}
}

#endif
