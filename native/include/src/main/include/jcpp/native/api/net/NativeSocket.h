#ifndef JCPP_NATIVE_API_NET_NATIVESOCKET
#define JCPP_NATIVE_API_NET_NATIVESOCKET

#include "jcpp/native/api/io/NativeInputStream.h"
#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/net/NativeInetSocketAddress.h"

using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				class JCPP_EXPORT NativeSocket {

				private:
					NativeSocket(const NativeSocket&);
					NativeSocket& operator =(const NativeSocket&);

				protected:
					NativeInetSocketAddress remoteSocketAddress;
					NativeInetSocketAddress localSocketAddress;

					jbool keepAliveSet;
					jbool keepAlive;

					jbool oobInlineSet;
					jbool oobInline;

					jbool receiveBufferSizeSet;
					jint receiveBufferSize;

					jbool reuseAddressSet;
					jbool reuseAddress;

					jbool sendBufferSizeSet;
					jint sendBufferSize;

					jbool soLingerSet;
					jbool soLingerOn;
					jint soLinger;

					jbool soTimeoutSet;
					jint soTimeout;

					jbool tcpNoDelaySet;
					jbool tcpNoDelay;

					NativeSocket();

					NativeSocket(const NativeInetSocketAddress& remoteSocketAddress, const NativeInetSocketAddress& localSocketAddress);
				public:
					virtual ~NativeSocket();

					//~-------------------------------------------------------------------------------------------
					//~ Local | Remote Inet Socket Addresses
					//~-------------------------------------------------------------------------------------------

					/**
					 * Returns the remote socket address.
					 */
					NativeInetSocketAddress getRemoteSocketAddress() const;

					/**
					 * Returns the local socket address.
					 */
					NativeInetSocketAddress getLocalSocketAddress() const;

					//~-------------------------------------------------------------------------------------------
					//~ Socket bind | connect | close
					//~-------------------------------------------------------------------------------------------

					/**
					 * Binds the socket to the local address.
					 */
					virtual void bind(const NativeInetSocketAddress& localSocketAddress) = 0;

					/**
					 * Connects this socket to the remote server.
					 */
					virtual void connect(const NativeInetSocketAddress& remoteSocketAddress, jint timeout = 0) = 0;

					/**
					 * Closes this socket.
					 */
					virtual void close() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ Socket Input | Output Streams
					//~-------------------------------------------------------------------------------------------

					/*
					 * Returns an input stream for this socket.
					 */
					virtual NativeInputStream * getInputStream() = 0;

					/**
					 * Returns an output stream for this socket.
					 */
					virtual NativeOutputStream * getOutputStream() = 0;

					/**
					 * Places the input stream for this socket at "end of stream".
					 */
					virtual void shutdownInput() = 0;

					/**
					 * Disables the output stream for this socket.
					 */
					virtual void shutdownOutput() = 0;

					/**
					 * Returns whether the read-half of the socket connection is closed.
					 */
					virtual jbool isInputShutdown() = 0;

					/**
					 * Returns whether the write-half of the socket connection is closed.
					 */
					virtual jbool isOutputShutdown() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ Bound | Closed | Connected Check
					//~-------------------------------------------------------------------------------------------

					/**
					 * Returns the binding state of the socket.
					 */
					virtual jbool isBound() = 0;

					/**
					 * Returns the closed state of the socket.
					 */
					virtual jbool isClosed() = 0;

					/**
					 * Returns the connection state of the socket.
					 */
					virtual jbool isConnected() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ Send Urgent Data
					//~-------------------------------------------------------------------------------------------

					/**
					 * Send one byte of urgent data on the socket.
					 */
					virtual void sendUrgentData(jbyte data) = 0;

					//~-------------------------------------------------------------------------------------------
					//~ Socket Options
					//~-------------------------------------------------------------------------------------------

					/**
					 * Tests if SO_KEEPALIVE is enabled.
					 */
					virtual jbool getKeepAlive() = 0;

					/**
					 * Enable/disable SO_KEEPALIVE.
					 */
					virtual void setKeepAlive(jbool on) = 0;

					/**
					 * Tests if OOBINLINE is enabled.
					 */
					virtual jbool getOOBInline() = 0;

					/**
					 * Enable/disable OOBINLINE (receipt of TCP urgent data) By default, this option is disabled
					 * and TCP urgent data received on a socket is silently discarded. If the user wishes to receive
					 * urgent data, then this option must be enabled. When enabled, urgent data is received
					 * inline with normal data.
					 */
					virtual void setOOBInline(jbool on) = 0;

					/**
					 * Gets the value of the SO_RCVBUF option for this Socket, that is the buffer size used by the
					 * platform for input on this Socket.
					 */
					virtual jint getReceiveBufferSize() = 0;

					/**
					 * Sets the SO_RCVBUF option to the specified value for this Socket.
					 * The SO_RCVBUF option is used by the platform's
					 * networking code as a hint for the size to set
					 * the underlying network I/O buffers.
					 *
					 * Increasing the receive buffer size can increase the performance of
					 * network I/O for high-volume connection, while decreasing it can
					 * help reduce the backlog of incoming data.
					 *
					 * Because SO_RCVBUF is a hint, applications that want to
					 * verify what size the buffers were set to should call
					 * getReceiveBufferSize().
					 *
					 * The value of SO_RCVBUF is also used to set the TCP receive window
					 * that is advertized to the remote peer. Generally, the window size
					 * can be modified at any time when a socket is connected. However, if
					 * a receive window larger than 64K is required then this must be requested
					 * before the socket is connected to the remote peer. There are two
					 * cases to be aware of:
					 *
					 * - For sockets accepted from a ServerSocket, this must be done by calling
					 * NativeServerSocket.setReceiveBufferSize before the ServerSocket
					 * is bound to a local address.
					 * - For client sockets, setReceiveBufferSize() must be called before
					 * connecting the socket to its remote peer.
					 */
					virtual void setReceiveBufferSize(jint size) = 0;

					/**
					 * Tests if SO_REUSEADDR is enabled.
					 */
					virtual jbool getReuseAddress() = 0;

					/**
					 * Enable/disable the SO_REUSEADDR socket option.
					 * When a TCP connection is closed the connection may remain
					 * in a timeout state for a period of time after the connection
					 * is closed (typically known as the TIME_WAIT state
					 * or 2MSL wait state).
					 * For applications using a well known socket address or port
					 * it may not be possible to bind a socket to the required
					 * SocketAddress if there is a connection in the
					 * timeout state involving the socket address or port.
					 *
					 * Enabling SO_REUSEADDR prior to binding the socket
					 * using bind allows the socket to be
					 * bound even though a previous connection is in a timeout
					 * state.
					 *
					 * When a Socket is created the initial setting
					 * of SO_REUSEADDR is disabled.
					 *
					 * The behaviour when SO_REUSEADDR is enabled or
					 * disabled after a socket is bound is not defined.
					 */
					virtual void setReuseAddress(jbool on) = 0;

					/**
					 * Get value of the SO_SNDBUF option for this Socket, that is the buffer size used by the platform for output on this Socket.
					 */
					virtual jint getSendBufferSize() = 0;

					/**
					 * Sets the SO_SNDBUF option to the specified value for this Socket.
					 * The SO_SNDBUF option is used by the platform's
					 * networking code as a hint for the size to set
					 * the underlying network I/O buffers.
					 */
					virtual void setSendBufferSize(jint size) = 0;

					/**
					 * Returns setting for SO_LINGER. -1 returns implies that the
					 * option is disabled. The setting only affects socket close.
					 */
					virtual jint getSoLinger() = 0;

					/**
					 * Enable/disable SO_LINGER with the specified linger time in seconds.
					 * The maximum timeout value is platform specific.
					 * The setting only affects socket close.
					 */
					virtual void setSoLinger(jbool on, jint linger) = 0;

					/**
					 * Returns setting for SO_TIMEOUT. 0 returns implies that the
					 * option is disabled (i.e., timeout of infinity).
					 */
					virtual jint getSoTimeout() = 0;

					/**
					 * Enable/disable SO_TIMEOUT with the specified timeout, in milliseconds.
					 * With this option set to a non-zero timeout,
					 * a read() call on the InputStream associated with this Socket
					 * will block for only this amount of time.  If the timeout expires,
					 * a SocketTimeoutException is raised, though the
					 * Socket is still valid. The option must be enabled
					 * prior to entering the blocking operation to have effect. The
					 * timeout must be > 0.
					 * A timeout of zero is interpreted as an infinite timeout.
					 */
					virtual void setSoTimeout(jint timeout) = 0;

					/**
					 * Tests if TCP_NODELAY is enabled.
					 */
					virtual jbool getTcpNoDelay() = 0;

					/**
					 * Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
					 */
					virtual void setTcpNoDelay(jbool on) = 0;

					/**
					 * Gets traffic class or type-of-service in the IP header for packets sent from this Socket
					 * As the underlying network implementation may ignore the
					 * traffic class or type-of-service set using {@link #setTrafficClass(int)}
					 * this method may return a different value than was previously
					 * set using the {@link #setTrafficClass(int)} method on this Socket.
					 */
					// TODO virtual jint getTrafficClass() = 0;
					/**
					 * Sets traffic class or type-of-service octet in the IP header for packets sent from this Socket.
					 * As the underlying network implementation may ignore this
					 * value applications should consider it a hint.
					 *
					 * The tc must be in the range 0 <= tc <= 255
					 * or an IllegalArgumentException will be thrown.
					 *
					 * Notes:
					 *
					 * For Internet Protocol v4 the value consists of an
					 * integer, the least significant 8 bits of which
					 * represent the value of the TOS octet in IP packets sent by
					 * the socket.
					 * RFC 1349 defines the TOS values as follows:
					 *
					 * -IPTOS_LOWCOST (0x02)
					 * -IPTOS_RELIABILITY (0x04)
					 * -IPTOS_THROUGHPUT (0x08)
					 * -IPTOS_LOWDELAY (0x10)
					 *
					 * The last low order bit is always ignored as this
					 * corresponds to the MBZ (must be zero) bit.
					 *
					 * Setting bits in the precedence field may result in a
					 * SocketException indicating that the operation is not
					 * permitted.
					 *
					 * As RFC 1122 section 4.2.4.2 indicates, a compliant TCP
					 * implementation should, but is not required to, let application
					 * change the TOS field during the lifetime of a connection.
					 * So whether the type-of-service field can be changed after the
					 * TCP connection has been established depends on the implementation
					 * in the underlying platform. Applications should not assume that
					 * they can change the TOS field after the connection.
					 *
					 * For Internet Protocol v6 tc< is the value that
					 * would be placed into the sin6_flowinfo field of the IP header.
					 */
					// TODO check if jbyte should be used
					// TODO virtual void setTrafficClass(jint tc) = 0;
				};

			}
		}
	}

}

#endif
