#ifndef JCPP_IO_JIOERROR_H
#define JCPP_IO_JIOERROR_H

#include "jcpp/lang/JError.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.IOError", simpleName="IOError");
        class JCPP_EXPORT JIOError : public JError {
        private:
       				static const jlong serialVersionUID = 67100927991680413LL;
            public:
                static jcpp::lang::JClass* getClazz();

                JIOError(JString* message);

                JIOError();

                JIOError(JThrowable* cause);

                virtual ~JIOError();
        };
    }
}

#endif
