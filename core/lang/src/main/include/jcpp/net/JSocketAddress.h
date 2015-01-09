#ifndef JCPP_NET_JSOCKETADDRESS_H
#define JCPP_NET_JSOCKETADDRESS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp {

	namespace net {

		//@Class(canonicalName="java.net.SocketAddress", simpleName="SocketAddress");
		class JCPP_EXPORT JSocketAddress: public JObject, public JSerializable {
		private:
				static const jlong serialVersionUID = 5215720748342549866LL;
		protected:
			JSocketAddress(JClass* _class);

		public:
			static JClass* getClazz();

			virtual ~JSocketAddress();

		};

	}

}

#endif
