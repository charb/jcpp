#ifndef JCPP_NET_JINETSOCKETADDRESS_H
#define JCPP_NET_JINETSOCKETADDRESS_H

#include "jcpp/net/JSocketAddress.h"
#include "jcpp/net/JInetAddress.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/native/api/net/NativeInetSocketAddress.h"

using namespace jcpp::lang;

namespace jcpp {

	namespace net {
		/* Note: Java InetSocketAddressHolder class was merjed with this class.
		 *
		 */

		//@Class(canonicalName="java.net.InetSocketAddress", simpleName="InetSocketAddress");
		class JCPP_EXPORT JInetSocketAddress: public JSocketAddress {

		private:
			static const jlong serialVersionUID = 5076001401234631237LL;

		private:
			JString* hostname;
			JPrimitiveInt* port;
			JInetAddress* addr;

			static jint checkPort(jint port);
			static JString* checkHost(JString* hostname);

			JInetSocketAddress();
			JInetSocketAddress(jint port, JString* hostname); // private constructor to create unresolved instances

			static JPrimitiveObjectArray* serialPersistentFields;
            static JPrimitiveObjectArray* getSerialPersistentFields();
            virtual void readObject(JObjectInputStream* s);
			virtual void writeObject(JObjectOutputStream* s);

		public:
			static JClass* getClazz();

			static JInetSocketAddress* createUnresolved(JString* host, jint port);

			JInetSocketAddress(jint port);

			JInetSocketAddress(JInetAddress* addr, jint port);

			JInetSocketAddress(JString* hostname, jint port);

			virtual jint getPort();

			virtual JInetAddress* getAddress();

			virtual JString* getHostName();

			virtual JString* getHostString();

			virtual jbool isUnresolved();

			virtual JString* toString();

			virtual jbool equals(JObject* obj);

			virtual jint hashCode();

			virtual ~JInetSocketAddress();

		};

	}

}

#endif
