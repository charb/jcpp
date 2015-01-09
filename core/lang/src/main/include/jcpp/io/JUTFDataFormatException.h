#ifndef JCPP_IO_JUTFDATAFORMATEXCEPTION_H
#define JCPP_IO_JUTFDATAFORMATEXCEPTION_H

#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.UTFDataFormatException", simpleName="UTFDataFormatException");
        class JCPP_EXPORT JUTFDataFormatException : public JIOException{
        private:
       		static const jlong serialVersionUID = 420743449228280612LL;
        public:
            JUTFDataFormatException();

            JUTFDataFormatException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JUTFDataFormatException();
        };
    }
}

#endif
