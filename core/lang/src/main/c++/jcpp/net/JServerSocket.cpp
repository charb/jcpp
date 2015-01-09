#include "jcpp/net/JServerSocket.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/net/JSocketException.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;

namespace jcpp {
	namespace net {


		JServerSocket::JServerSocket(JClass* _class) : JObject(_class) {
			init(0, 0, null, false);
		}

		JServerSocket::JServerSocket(JClass* _class,jint port, jint backlog): JObject(_class) {
			init(port, backlog, null, true);
		}

		JServerSocket::JServerSocket(JClass* _class,jint port, jint backlog, JInetAddress* bindAddr): JObject(_class){
			init(port, backlog, bindAddr, true);
		}

		JServerSocket::JServerSocket() : JObject(getClazz()) {
			init(0, 0, null, false);
		}

		JServerSocket::JServerSocket(jint port): JObject(getClazz()) {
			init(port, 0, null, true);
		}

		JServerSocket::JServerSocket(jint port, jint backlog): JObject(getClazz()) {
			init(port, backlog, null, true);
		}

		JServerSocket::JServerSocket(jint port, jint backlog, JInetAddress* bindAddr): JObject(getClazz()) {
			init(port, backlog, bindAddr, true);
		}

		void JServerSocket::init(jint port, jint backlog, JInetAddress* bindAddr, jbool bindNatively) {
			nativeServerSocket = null;
			if (port < 0 || port > 0xFFFF) {
				throw new JIllegalArgumentException((new JStringBuilder())->append("Port value out of range: ")->append(port)->toString());
			}
			TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket = NativeFactory::getNativeNetFactory()->createNativeServerSocket(); })
			if(bindNatively)  {
				if (backlog < 1) {
					backlog = 50;
				}
				try {
					bind(new JInetSocketAddress(bindAddr == null ? JInetAddress::getLocalHost() : bindAddr, port), backlog);
				} catch(JThrowable* throwable) {
					try{
						close();
					}catch(JThrowable* th2){
						th2->printStackTrace();
					}
					throw throwable;
				}
			}
		}

		void JServerSocket::bind(JSocketAddress* endpoint, jint backlog) {
			if (isClosed()) {
				throw new JSocketException(new JString("Socket is closed"));
			}
			if (isBound()) {
				throw new JSocketException(new JString("Already bound"));
			}
			if(endpoint != null && !endpoint->isInstanceOf(JInetSocketAddress::getClazz())) {
				throw new JIllegalArgumentException(new JString("Unsupported address type"));
			}
			if (backlog < 1) {
				backlog = 50;
			}

			if(endpoint == null) {
				TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket->bind(NativeInetSocketAddress(JInetAddress::getLocalHost()->createNativeInetAddress(), 0), backlog); })
			} else {
				JInetSocketAddress* socketAddr = dynamic_cast<JInetSocketAddress*>(endpoint);
				if(socketAddr->isUnresolved()) {
					throw new JSocketException(new JString("Unresolved address"));
				}
				TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket->bind(NativeInetSocketAddress(socketAddr->getAddress()->createNativeInetAddress(), socketAddr->getPort()), backlog); })
			}
		}

		JInetAddress* JServerSocket::getInetAddress() {
			if(!isBound()) {
				return null;
			}
			NativeInetSocketAddress localSocketAddress = nativeServerSocket->getLocalSocketAddress();
			return JInetAddress::createInetAddress(localSocketAddress.getHost());
		}

		jint JServerSocket::getLocalPort() {
			if(!isBound()) {
				return 0;
			}
			NativeInetSocketAddress localSocketAddress = nativeServerSocket->getLocalSocketAddress();
			return localSocketAddress.getPort();
		}

		JSocketAddress* JServerSocket::getLocalSocketAddress() {
			if(!isBound()) {
				return null;
			}
			NativeInetSocketAddress localSocketAddress = nativeServerSocket->getLocalSocketAddress();
			return new JInetSocketAddress(JInetAddress::createInetAddress(localSocketAddress.getHost()), localSocketAddress.getPort());
		}

		JSocket* JServerSocket::accept() {
			if (!isBound()) {
				throw new JSocketException(new JString("Socket is not bound yet"));
			}
			NativeSocket* nativeSocket = null;
			TRY_CATCH_NATIVE_EXCEPTION({ nativeSocket = nativeServerSocket->accept(); })
			return new JSocket(nativeSocket);
		}

		void JServerSocket::close() {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket->close(); })
		}

		jbool JServerSocket::isBound() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeServerSocket->isBound(); })
			return value;
		}

		jbool JServerSocket::isClosed() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeServerSocket->isClosed(); })
			return value;
		}

		void JServerSocket::setSoTimeout(jint timeout) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket->setSoTimeout(timeout); })
		}

		jint JServerSocket::getSoTimeout() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeServerSocket->getSoTimeout(); })
			return value;
		}

		void JServerSocket::setReuseAddress(jbool on) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket->setReuseAddress(on); })
		}

		jbool JServerSocket::getReuseAddress() {
			jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeServerSocket->getReuseAddress(); })
			return value;
		}

		void JServerSocket::setReceiveBufferSize (jint size) {
			TRY_CATCH_NATIVE_EXCEPTION({ nativeServerSocket->setReceiveBufferSize(size); })
		}

		jint JServerSocket::getReceiveBufferSize() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION({ value = nativeServerSocket->getReceiveBufferSize(); })
			return value;
		}

		JString* JServerSocket::toString() {
			if(!isBound()) {
				return new JString("ServerSocket[unbound]");
			}
			NativeInetSocketAddress localSocketAddress = nativeServerSocket->getLocalSocketAddress();
			return (new JStringBuilder())->append("ServerSocket[addr=")->append(JInetAddress::createInetAddress(localSocketAddress.getHost()))->append(",localport=")->append(localSocketAddress.getPort())->append("]")->toString();
		}

		void JServerSocket::finalize() {
			if(nativeServerSocket != null) {
				TRY_CATCH_NATIVE_EXCEPTION({ delete nativeServerSocket; })
				nativeServerSocket = null;
			}
		}

		JServerSocket::~JServerSocket() {
		}
	}
}
