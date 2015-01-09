#ifndef JCPP_IO_JSYNCFAILEDEXCEPTION_H
#define JCPP_IO_JSYNCFAILEDEXCEPTION_H

#include "jcpp/io/JIOException.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.SyncFailedException", simpleName="SyncFailedException");
        class JCPP_EXPORT JSyncFailedException : public JIOException  {
        private:
       			static const jlong serialVersionUID = -2353342684412443330LL;
            public:
                static jcpp::lang::JClass* getClazz();

                JSyncFailedException();

                JSyncFailedException(JString* message);

                virtual ~JSyncFailedException();
        };
    }
}

#endif
