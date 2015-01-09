#ifndef JCPP_IO_JCHARCONVERSIONEXCEPTION_H
#define JCPP_IO_JCHARCONVERSIONEXCEPTION_H

#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.CharConversionException", simpleName="CharConversionException");
        class JCPP_EXPORT JCharConversionException : public JIOException  {
            public:
                static jcpp::lang::JClass* getClazz();

                JCharConversionException();

                JCharConversionException(JString* message);

                virtual ~JCharConversionException();
        };
    }
}

#endif

