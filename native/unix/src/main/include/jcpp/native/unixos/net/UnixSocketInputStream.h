#ifndef JCPP_NATIVE_UNIXOS_NET_UNIXSSOCKETINPUTSTREAM
#define JCPP_NATIVE_UNIXOS_NET_UNIXSSOCKETINPUTSTREAM

#include "jcpp/native/api/io/NativeInputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/unixos/UnixUtils.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				class UnixSocket;

				class JCPP_EXPORT UnixSocketInputStream: public NativeInputStream {

					friend class UnixSocket;

				private:
					static NativeString className;

					int socket;
					jbool eof;
					jint timeout;

					volatile jbool streamClosed;
					volatile jbool socketClosed;

					UnixSocketInputStream(const UnixSocketInputStream&);
					UnixSocketInputStream& operator =(const UnixSocketInputStream&);

					void markSocketClosed();

				public:
					UnixSocketInputStream(int socket);
					virtual ~UnixSocketInputStream();

					virtual jbyte read();
					virtual jint read(jbyte * buf, jint offset, jint length);
					virtual jlong skip(jlong offset);
					virtual jlong available();
					virtual void close();

					jbool isStreamClosed();
					jint getSoTimeout();
					void setSoTimeout(jint timeout);

				};

			}
		}
	}
}

#endif
