#ifndef JCPP_IO_JNOTSERIALIZABLEEXCEPTION_H
#define JCPP_IO_JNOTSERIALIZABLEEXCEPTION_H

#include "jcpp/io/JObjectStreamException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.NotSerializableException", simpleName="NotSerializableException");
        class JCPP_EXPORT JNotSerializableException : public JObjectStreamException{
        private:
       		static const jlong serialVersionUID = 2906642554793891381LL;
        protected:
            JNotSerializableException(jcpp::lang::JClass* _clazz);

        public:
            JNotSerializableException();

            JNotSerializableException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNotSerializableException();
        };
    }
}

#endif
