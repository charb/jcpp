#ifndef JCPP_IO_JEXTERNALIZABLE_H
#define JCPP_IO_JEXTERNALIZABLE_H

#include "jcpp/lang/JClass.h"
#include "jcpp/io/JObjectOutput.h"
#include "jcpp/io/JObjectInput.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace lang {
		class JClass;
	}

	namespace io {

		//@Class(canonicalName="java.io.Externalizable", simpleName="Externalizable");
		class JCPP_EXPORT JExternalizable: public JSerializable {
		public:
			static jcpp::lang::JClass* getClazz();

			virtual void writeExternal(JObjectOutput* out)=0;

			virtual void readExternal(JObjectInput* in)=0;

			virtual ~JExternalizable();
		};
	}
}

#endif
