#ifndef JCPP_IO_JINVALIDOBJECTEXCEPTION_H
#define JCPP_IO_JINVALIDOBJECTEXCEPTION_H

#include "jcpp/io/JObjectStreamException.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.InvalidObjectException", simpleName="InvalidObjectException");
        class JCPP_EXPORT JInvalidObjectException : public JObjectStreamException{
        private:
       				static const jlong serialVersionUID = 3233174318281839583LL;
        public:
            JInvalidObjectException();

            JInvalidObjectException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JInvalidObjectException();
        };
    }
}
#endif
