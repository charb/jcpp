#ifndef JCPP_NATIVE_UNIX_NET_UNIXSOCKETOUTPUTSTREAM
#define JCPP_NATIVE_UNIX_NET_UNIXSOCKETOUTPUTSTREAM

#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/unixos/UnixUtils.h"


using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				class UnixSocket;

				class JCPP_EXPORT UnixSocketOutputStream: public NativeOutputStream {

					friend class UnixSocket;

				private:
					static NativeString className;

					int socket;

					volatile jbool streamClosed;
					volatile jbool socketClosed;

					UnixSocketOutputStream(const UnixSocketOutputStream&);
					UnixSocketOutputStream& operator =(const UnixSocketOutputStream&);

					void markSocketClosed();

				public:
					UnixSocketOutputStream(int socket);
					virtual ~UnixSocketOutputStream();

					virtual void write(jbyte byte);
					virtual void write(jbyte * buf, jint offset, jint length);
					virtual void flush();
					virtual void close();

					jbool isStreamClosed();

				};

			}
		}
	}

}

#endif
