#ifndef JCPP_NET_JSOCKETTIMEOUTEXCEPTION_H_
#define JCPP_NET_JSOCKETTIMEOUTEXCEPTION_H_

#include "jcpp/io/JInterruptedIOException.h"

using namespace jcpp::io;

namespace jcpp{
    namespace net{

		//@Class(canonicalName="java.net.SocketTimeoutException", simpleName="SocketTimeoutException");
        class JCPP_EXPORT JSocketTimeoutException : public  JInterruptedIOException{
    	private:
    		static const jlong serialVersionUID = -8846654841826352300LL;
    	protected:
    		JSocketTimeoutException(jcpp::lang::JClass* _class);
            public:
                static jcpp::lang::JClass* getClazz();

                JSocketTimeoutException();

                JSocketTimeoutException(JString* message);

                virtual ~JSocketTimeoutException();
        };
    }
}


#endif /* JCPP_NET_JSOCKETTIMEOUTEXCEPTION_H_ */
