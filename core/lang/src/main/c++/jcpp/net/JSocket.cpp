#include "jcpp/net/JSocket.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/net/JSocketException.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/io/JNativeInputStream.h"
#include "jcpp/io/JNativeOutputStream.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;

namespace jcpp {
	namespace net {

		JSocket::JSocket(JClass* _class) : JObject(_class) {
			init(null, null, null);
		}

		JSocket::JSocket(NativeSocket* socket) : JObject(getClazz()) {
			init(null, null, socket);
		}

		JSocket::JSocket() : JObject(getClazz()) {
			init(null, null, null);
		}

		JSocket::JSocket(JString* host, jint port) : JObject(getClazz()) {
			JInetSocketAddress* address = host != null ? new JInetSocketAddress(host, port) : new JInetSocketAddress(JInetAddress::getByName(null), port);
			init(address, null, null);
		}

		JSocket::JSocket(JInetAddress* address, jint port) : JObject(getClazz()) {
			if(address == null) {
				throw new JIllegalArgumentException(new JString("Invalid null address!"));
			}
			init(new JInetSocketAddress(address, port), null, null);
		}

		JSocket::JSocket(JString* host, jint port, JInetAddress* localAddr, jint localPort) : JObject(getClazz()) {
			JInetSocketAddress* address = host != null ? new JInetSocketAddress(host, port) : new JInetSocketAddress(JInetAddress::getByName(null), port);
			JInetSocketAddress* localAddress = localAddr != null ? new JInetSocketAddress(localAddr, localPort) : null;
			init(address, localAddress, null);
		}

		JSocket::JSocket(JInetAddress* address, jint port, JInetAddress* localAddr, jint localPort) : JObject(getClazz()) {
			if(address == null) {
				throw new JIllegalArgumentException(new JString("Invalid null address!"));
			}
			JInetSocketAddress* localAddress = localAddr != null ? new JInetSocketAddress(localAddr, localPort) : null;
			init(new JInetSocketAddress(address, port), localAddress, null);
		}

		void JSocket::init(JInetSocketAddress* address, JInetSocketAddress* localAddress, NativeSocket* socket) {
			nativeSocket = null;
			inputStream = null;
			outputStream = null;
			if(socket == null)  {
				TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket = NativeFactory::getNativeNetFactory()->createNativeSocket(); })
				try {
					if(localAddress != null) {
						bind(localAddress);
					}
					if(address != null) {
						connect(address);
					}
				} catch(JThrowable* e) {
					close();
					throw e;
				}
			} else {
				nativeSocket = socket;
			}
		}

		void JSocket::bind(JSocketAddress* bindpoint) {
			if (isClosed()) {
				throw new JSocketException(new JString("Socket is closed"));
			}
			if (isBound()) {
				throw new JSocketException(new JString("Already bound"));
			}
			if(bindpoint != null && !bindpoint->isInstanceOf(JInetSocketAddress::getClazz())) {
				throw new JIllegalArgumentException(new JString("Unsupported address type"));
			}
			if(bindpoint == null) {
				TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->bind(NativeInetSocketAddress(JInetAddress::getLocalHost()->createNativeInetAddress(), 0)); })
			} else {
				JInetSocketAddress* socketAddr = dynamic_cast<JInetSocketAddress*>(bindpoint);
				if(socketAddr->isUnresolved()) {
					throw new JSocketException(new JString("Unresolved address"));
				}
				TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->bind(NativeInetSocketAddress(socketAddr->getAddress()->createNativeInetAddress(), socketAddr->getPort())); })
			}
		}

		void JSocket::connect(JSocketAddress* endpoint, jint timeout) {
			if (endpoint == null) {
				throw new JIllegalArgumentException(new JString("connect: The address can't be null"));
			}
			if (timeout < 0) {
				throw new JIllegalArgumentException(new JString("connect: timeout can't be negative"));
			}
			if (isClosed()) {
				throw new JSocketException(new JString("Socket is closed"));
			}
			if(!endpoint->isInstanceOf(JInetSocketAddress::getClazz())) {
				throw new JIllegalArgumentException(new JString("Unsupported address type"));
			}
			JInetSocketAddress* socketAddr = dynamic_cast<JInetSocketAddress*>(endpoint);
			if(socketAddr->isUnresolved()) {
				throw new JSocketException(new JString("Unresolved address"));
			}
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->connect(NativeInetSocketAddress(socketAddr->getAddress()->createNativeInetAddress(), socketAddr->getPort()), timeout); })
		}

		void JSocket::close() {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->close(); })
		}

		jbool JSocket::isConnected() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->isConnected(); })
			return value;
		}

		jbool JSocket::isBound() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->isBound(); })
			return value;
		}

		jbool JSocket::isClosed() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->isClosed(); })
			return value;
		}

		JInetAddress* JSocket::getInetAddress() {
			if(!isConnected()) {
				return null;
			}
			NativeInetSocketAddress socketAddress = nativeSocket->getRemoteSocketAddress();
			return JInetAddress::createInetAddress(socketAddress.getHost());
		}

		JInetAddress* JSocket::getLocalAddress() {
			if(!isBound()) {
				return null;
			}
			NativeInetSocketAddress socketAddress = nativeSocket->getLocalSocketAddress();
			return JInetAddress::createInetAddress(socketAddress.getHost());
		}

		jint JSocket::getPort() {
			if(!isConnected()) {
				return 0;
			}
			NativeInetSocketAddress socketAddress = nativeSocket->getRemoteSocketAddress();
			return socketAddress.getPort();
		}

		jint JSocket::getLocalPort() {
			if(!isBound()) {
				return 0;
			}
			NativeInetSocketAddress socketAddress = nativeSocket->getLocalSocketAddress();
			return socketAddress.getPort();
		}

		JSocketAddress* JSocket::getRemoteSocketAddress() {
			if(!isConnected()) {
				return null;
			}
			NativeInetSocketAddress socketAddress = nativeSocket->getRemoteSocketAddress();
			return new JInetSocketAddress(JInetAddress::createInetAddress(socketAddress.getHost()), socketAddress.getPort());
		}

		JSocketAddress* JSocket::getLocalSocketAddress() {
			if(!isBound()) {
				return null;
			}
			NativeInetSocketAddress socketAddress = nativeSocket->getLocalSocketAddress();
			return new JInetSocketAddress(JInetAddress::createInetAddress(socketAddress.getHost()), socketAddress.getPort());
		}

		JInputStream* JSocket::getInputStream() {
			if (isClosed()) {
				throw new JSocketException(new JString("Socket is closed"));
			}
			if (!isConnected()) {
				throw new JSocketException(new JString("Socket is not connected"));
			}
			if (isInputShutdown()) {
				throw new JSocketException(new JString("Socket input is shutdown"));
			}
			if(inputStream == null) {
				NativeInputStream * nativeInputStream = null;
				TRY_CATCH_NATIVE_EXCEPTION({ nativeInputStream = nativeSocket->getInputStream(); })
				if(nativeInputStream != null) {
					inputStream = new JNativeInputStream(nativeInputStream, true);
				}
			}
			return inputStream;
		}

		JOutputStream* JSocket::getOutputStream() {
			if (isClosed()) {
				throw new JSocketException(new JString("Socket is closed"));
			}
			if (!isConnected()) {
				throw new JSocketException(new JString("Socket is not connected"));
			}
			if (isOutputShutdown()) {
				throw new JSocketException(new JString("Socket output is shutdown"));
			}
			if(outputStream == null) {
				NativeOutputStream * nativeOutputStream = null;
				TRY_CATCH_NATIVE_EXCEPTION({ nativeOutputStream = nativeSocket->getOutputStream(); })
				if(nativeOutputStream != null) {
					outputStream = new JNativeOutputStream(nativeOutputStream, true);
				}
			}
			return outputStream;
		}

		void JSocket::shutdownInput() {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->shutdownInput(); })
		}

		void JSocket::shutdownOutput() {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->shutdownOutput(); })
		}

		jbool JSocket::isInputShutdown() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->isInputShutdown(); })
			return value;
		}

		jbool JSocket::isOutputShutdown() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->isOutputShutdown(); })
			return value;
		}

		void JSocket::sendUrgentData (jint data) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->sendUrgentData(data); })
		}

		void JSocket::setTcpNoDelay(jbool on) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setTcpNoDelay(on); })
		}

		jbool JSocket::getTcpNoDelay() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getTcpNoDelay(); })
			return value;
		}

		void JSocket::setSoLinger(jbool on, jint linger) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setSoLinger(on, linger); })
		}

		jint JSocket::getSoLinger() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getSoLinger(); })
			return value;
		}

		void JSocket::setOOBInline(jbool on) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setOOBInline(on); })
		}

		jbool JSocket::getOOBInline() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getOOBInline(); })
			return value;
		}

		void JSocket::setSoTimeout(jint timeout) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setSoTimeout(timeout); })
		}

		jint JSocket::getSoTimeout() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getSoTimeout(); })
			return value;
		}

		void JSocket::setSendBufferSize(jint size) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setSendBufferSize(size); })
		}

		jint JSocket::getSendBufferSize() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getSendBufferSize(); })
			return value;
		}

		void JSocket::setReceiveBufferSize(jint size) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setReceiveBufferSize(size); })
		}

		jint JSocket::getReceiveBufferSize() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getReceiveBufferSize(); })
			return value;
		}

		void JSocket::setKeepAlive(jbool on) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setKeepAlive(on); })
		}

		jbool JSocket::getKeepAlive() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getKeepAlive(); })
			return value;
		}

		void JSocket::setReuseAddress(jbool on)  {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket->setReuseAddress(on); })
		}

		jbool JSocket::getReuseAddress() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeSocket->getReuseAddress(); })
			return value;
		}

		JString* JSocket::toString()  {
			if(!isConnected()) {
				return new JString("Socket[unconnected]");
			}
			NativeInetSocketAddress localSA = nativeSocket->getLocalSocketAddress();
			NativeInetSocketAddress remoteSA = nativeSocket->getRemoteSocketAddress();
			return (new JStringBuilder())->append("Socket[addr=")->append(JInetAddress::createInetAddress(remoteSA.getHost()))->append(",port=")->append(remoteSA.getPort())->append(",localport=")->append(localSA.getPort())->append("]")->toString();
		}

		void JSocket::finalize() {
			if(nativeSocket != null) {
				TRY_CATCH_NATIVE_EXCEPTION({ delete nativeSocket; })
				nativeSocket = null;
			}
		}

		JSocket::~JSocket() {
		}
	}
}
