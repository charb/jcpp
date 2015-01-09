#ifndef JCPP_IO_JEOFEXCEPTION_H
#define JCPP_IO_JEOFEXCEPTION_H

#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.EOFException", simpleName="EOFException");
        class JCPP_EXPORT JEOFException : public JIOException{
        private:
        	static const jlong serialVersionUID = 6433858223774886977LL;

        public:
            JEOFException();

            JEOFException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JEOFException();
        };
    }
}

#endif
