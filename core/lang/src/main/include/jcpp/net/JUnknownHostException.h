#ifndef JCPP_NET_JFILENOTFOUNDEXCEPTION_H
#define JCPP_NET_JFILENOTFOUNDEXCEPTION_H

#include "jcpp/io/JIOException.h"

using namespace jcpp::io;

namespace jcpp{
    namespace net{

		//@Class(canonicalName="java.net.Inet4Address", simpleName="Inet4Address");
        class JCPP_EXPORT JUnknownHostException : public JIOException  {
        private:
        		static const jlong serialVersionUID = -4639126076052875403LL;
            public:
                static jcpp::lang::JClass* getClazz();

                JUnknownHostException();

                JUnknownHostException(JString* message);

                virtual ~JUnknownHostException();
        };
    }
}

#endif
