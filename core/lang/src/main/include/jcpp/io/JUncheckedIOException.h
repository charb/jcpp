#ifndef JCPP_IO_JUNCHECKED_IOEXCEPTION_H
#define JCPP_IO_JUNCHECKED_IOEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.UncheckedIOException", simpleName="UncheckedIOException");
        class JCPP_EXPORT JUncheckedIOException : public JRuntimeException {
        private:
       				static const jlong serialVersionUID = -8134305061645241065LL;
            public:
                static jcpp::lang::JClass* getClazz();

                JUncheckedIOException();

                JUncheckedIOException(JString* message);

                virtual ~JUncheckedIOException();
        };
    }
}

#endif
