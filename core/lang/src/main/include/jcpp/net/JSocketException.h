#ifndef JCPP_NET_JSOCKETEXCEPTION_H
#define JCPP_NET_JSOCKETEXCEPTION_H

#include "jcpp/io/JIOException.h"

using namespace jcpp::io;

namespace jcpp{
    namespace net{

		//@Class(canonicalName="java.net.SocketException", simpleName="SocketException");
        class JCPP_EXPORT JSocketException : public JIOException  {
    	private:
    		static const jlong serialVersionUID = -5935874303556886934LL;

            public:
                static jcpp::lang::JClass* getClazz();

                JSocketException();

                JSocketException(JString* message);

                virtual ~JSocketException();
        };
    }
}

#endif
