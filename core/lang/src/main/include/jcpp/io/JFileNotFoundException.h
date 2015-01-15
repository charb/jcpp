#ifndef JCPP_IO_JFILENOTFOUNDEXCEPTION_H
#define JCPP_IO_JFILENOTFOUNDEXCEPTION_H

#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FileNotFoundException", simpleName="FileNotFoundException");
        class JCPP_EXPORT JFileNotFoundException : public JIOException  {
        private:
       				static const jlong serialVersionUID = 897856973823710492LL;
            public:
                static jcpp::lang::JClass* getClazz();

                JFileNotFoundException();

                JFileNotFoundException(JString* message);

                virtual ~JFileNotFoundException();
        };
    }
}

#endif
