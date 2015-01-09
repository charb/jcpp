#ifndef JCPP_NATIVE_UNIXOS_NET_UNIXSERVERSOCKET
#define JCPP_NATIVE_UNIXOS_NET_UNIXSERVERSOCKET

#include "jcpp/native/api/net/NativeServerSocket.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

using namespace jcpp::native::api::net;
using namespace jcpp::native::api;
using namespace jcpp::native::unixos::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				class JCPP_EXPORT UnixServerSocket: public NativeServerSocket {

				private:
					static NativeString className;

					UnixMutex mutex;

					jint timeout;
					jbool bound;
					jbool closed;

					int socket;

					UnixServerSocket(const UnixServerSocket&);
					UnixServerSocket& operator =(const UnixServerSocket&);

				public:

					UnixServerSocket();
					virtual ~UnixServerSocket();

					virtual void bind(const NativeInetSocketAddress& socketAddress, const jint backlog = 50);
					virtual NativeSocket * accept();
					virtual void close();

					virtual jbool isBound();
					virtual jbool isClosed();

					virtual jint getReceiveBufferSize();
					virtual void setReceiveBufferSize(jint size);
					virtual jbool getReuseAddress();
					virtual void setReuseAddress(jbool on);
					virtual jint getSoTimeout();
					virtual void setSoTimeout(jint timeout);

				};

			}
		}
	}
}

#endif
