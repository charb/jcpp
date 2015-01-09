#ifndef JCPP_NATIVE_API_NET_NATIVESERVERSOCKET
#define JCPP_NATIVE_API_NET_NATIVESERVERSOCKET

#include "jcpp/native/api/net/NativeSocket.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				class JCPP_EXPORT NativeServerSocket {

				private:
					NativeServerSocket(const NativeServerSocket&);
					NativeServerSocket& operator =(const NativeServerSocket&);

				protected:
					jbool reuseAddressSet;
					jbool reuseAddress;

					jbool receiveBufferSizeSet;
					jint receiveBufferSize;

					NativeInetSocketAddress socketAddress;

					NativeServerSocket();

				public:
					virtual ~NativeServerSocket();

					//~-------------------------------------------------------------------------------------------
					//~ Inet Socket Address
					//~-------------------------------------------------------------------------------------------

					/**
					 * Returns the local socket address.
					 */
					NativeInetSocketAddress getLocalSocketAddress() const;

					//~-------------------------------------------------------------------------------------------
					//~ Socket bind | accept  | close
					//~-------------------------------------------------------------------------------------------

					/**
					 * Binds the ServerSocket to a specific address (IP address and port number).
					 */
					virtual void bind(const NativeInetSocketAddress& socketAddress, const jint backlog = 50) = 0;

					/**
					 * Listens for a connection to be made to this socket and accepts it.
					 */
					virtual NativeSocket * accept() = 0;

					/**
					 * Closes this socket.
					 */
					virtual void close() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ Bound | Closed Check
					//~-------------------------------------------------------------------------------------------

					/**
					 * Returns the binding state of the ServerSocket.
					 */
					virtual jbool isBound() = 0;

					/**
					 * Returns the closed state of the ServerSocket.
					 */
					virtual jbool isClosed() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ Server Socket Options
					//~-------------------------------------------------------------------------------------------

					/**
					 * Gets the value of the SO_RCVBUF option for this ServerSocket, that is the proposed buffer size
					 * that will be used for Sockets accepted from this ServerSocket.
					 */
					virtual jint getReceiveBufferSize() = 0;

					/**
					 * Sets a default proposed value for the SO_RCVBUF option for sockets
					 * accepted from this ServerSocket. The value actually set
					 * in the accepted socket must be determined by calling
					 * NativeSocket.getReceiveBufferSize() after the socket
					 * is returned by accept().
					 *
					 * The value of SO_RCVBUF is used both to set the size of the internal
					 * socket receive buffer, and to set the size of the TCP receive window
					 * that is advertized to the remote peer.
					 *
					 * It is possible to change the value subsequently, by calling
					 * NativeSocket.setReceiveBufferSize(int). However, if the application
					 * wishes to allow a receive window larger than 64K bytes, as defined by RFC1323
					 * then the proposed value must be set in the ServerSocket before>
					 * it is bound to a local address. This implies, that the ServerSocket must be
					 * created with the no-argument constructor, then setReceiveBufferSize() must
					 * be called and lastly the ServerSocket is bound to an address by calling bind().
					 *
					 * Failure to do this will not cause an error, and the buffer size may be set to the
					 * requested value but the TCP receive window in sockets accepted from
					 * this ServerSocket will be no larger than 64K bytes.
					 */
					virtual void setReceiveBufferSize(jint size) = 0;

					/**
					 *  Tests if SO_REUSEADDR is enabled.
					 */
					virtual jbool getReuseAddress() = 0;

					/**
					 * Enable/disable the SO_REUSEADDR socket option.
					 * When a TCP connection is closed the connection may remain in a timeout state for a period of time after
					 * the connection is closed (typically known as the TIME_WAIT state or 2MSL wait state). For applications
					 * using a well known socket address or port it may not be possible to bind a socket to the required
					 * SocketAddress if there is a connection in the timeout state involving the socket address or port.
					 * Enabling SO_REUSEADDR prior to binding the socket using bind(SocketAddress) allows the socket to be
					 * bound even though a previous connection is in a timeout state.
					 * When a ServerSocket is created the initial setting of SO_REUSEADDR is not defined.
					 * Applications can use getReuseAddress() to determine the initial setting of SO_REUSEADDR.
					 * The behaviour when SO_REUSEADDR is enabled or disabled after a socket is bound (See isBound()) is not defined.
					 */
					virtual void setReuseAddress(jbool on) = 0;

					/**
					 * Retrieve setting for SO_TIMEOUT.
					 */
					virtual jint getSoTimeout() = 0;

					/**
					 * Enable/disable SO_TIMEOUT with the specified timeout, in milliseconds.
					 * With this option set to a non-zero timeout, a call to accept() for this ServerSocket
					 * will block for only this amount of time. If the timeout expires, a Native Exception SocketTimeoutException
					 * is raised, though the ServerSocket is still valid. The option must be enabled prior to entering the blocking
					 * operation to have effect. The timeout must be > 0. A timeout of zero is interpreted as an infinite timeout.
					 */
					virtual void setSoTimeout(jint timeout) = 0;

				};

			}
		}
	}

}

#endif
