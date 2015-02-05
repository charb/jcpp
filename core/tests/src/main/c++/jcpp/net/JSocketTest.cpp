#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JBufferedReader.h"
#include "jcpp/io/JPrintWriter.h"
#include "jcpp/JAbstractTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/net/JSocketException.h"
#include "jcpp/net/JSocketTimeoutException.h"
#include "jcpp/net/JServerSocket.h"
#include "jcpp/net/JSocketTest.h"
#include "junit/framework/JTestCase.h"
#include "jcpp/io/JInputStreamReader.h"
#include "jcpp/net/JInet4Address.h"

using namespace jcpp::net;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::io;
using namespace junit::framework;

namespace jcpp {
	namespace net {

		//@Class(canonicalName="java.net.SocketTest$ClientSendRecieveThread", simpleName="SocketTest$ClientSendRecieveThread");
		class ClientSendRecieveThread: public JThread{

		public:

			JString* reachedString;
			jbyte ackByte;
			JException* timeoutException;

			ClientSendRecieveThread() :
					JThread(), ackByte(0), reachedString(NULL), timeoutException(NULL){
			}

			static JClass* getClazz();

			void ClientSendRecieveThread::run(){
				try{

					JSocket* ClientSocket = new JSocket(JInetAddress::getLocalHost(), 5268);
					ClientSocket->setOOBInline(true);
					JPrintWriter* ClientSocketOut = new JPrintWriter(ClientSocket->getOutputStream(), true);
					JObjectInputStream *ClientSocketIn = new JObjectInputStream(ClientSocket->getInputStream());
					JBufferedReader *ClientSocketUrgentIn = new JBufferedReader(new JInputStreamReader(ClientSocket->getInputStream()));

					JString* testString = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t,.;:!?[](){}!1234567890!@#$%^&*~-");

					//Send Tester String
					ClientSocketOut->println(testString);

					//receive TCP urgent data
					JPrimitiveCharArray *urgentBuffer = null;
					urgentBuffer = new JPrimitiveCharArray(2);
					ClientSocketUrgentIn->read(urgentBuffer, 0, 2);
					ackByte = static_cast<jbyte>(urgentBuffer->getChar(0));

					//receive Tester String
					JPrimitiveByteArray *readBuffer = null;
					readBuffer = new JPrimitiveByteArray(testString->length());
					ClientSocketIn->read(readBuffer, 0, testString->length());
					reachedString = new JString(readBuffer);

					ClientSocket->setSendBufferSize(2000);

					JStringBuilder *sb = new JStringBuilder();
					for (jint i = 0; i < 10000; i++){
						sb->append("a");
					}

					ClientSocketOut->println(sb->toString());
					ClientSocketOut->flush();

					ClientSocket->setSoTimeout(1000);

					ClientSocketIn->read();
					ClientSocketIn->read(readBuffer, 0, readBuffer->size());
					JSystem::out->println(new JString("No exception.."));
					ClientSocket->close();
				} catch (JException* t1){
					timeoutException = t1;
					//JSystem::out->println(t1->getMessage());
				} catch (...){
					JSystem::out->println(new JString("Unknown exception thrown"));
				}

			}

		};

		//@Class(canonicalName="java.net.SocketTest$ClientCloseSocketThread", simpleName="SocketTest$ClientCloseSocketThread");
		class ClientCloseSocketThread: public JThread{

		public:

			JException* inputClosedException;

			ClientCloseSocketThread() :
					JThread(), inputClosedException(NULL){
			}

			static JClass* getClazz();

			virtual void run(){
				try{
					JSocket* ClientSocket = new JSocket(JInetAddress::getLocalHost(), 5269);
					ClientSocket->setOOBInline(true);
					JPrintWriter* ClientSocketOut = new JPrintWriter(ClientSocket->getOutputStream(), true);
					JObjectInputStream *ClientSocketIn = new JObjectInputStream(ClientSocket->getInputStream());

					JString* testString = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t,.;:!?[](){}!1234567890!@#$%^&*~-");

					//Send Tester String
					ClientSocketOut->println(testString);
					ClientSocketOut->flush();

					ClientSocket->close();
					ClientSocketIn->read();
				} catch (JException* e){
					inputClosedException = e;
					//JSystem::out->println((new JStringBuilder())->append("Exception Thrown Message: ")->append(e->getMessage())->toString());
				} catch (...){
					JSystem::out->println(new JString("Unknown exception thrown"));
				}
			}

		};

		//@Class(canonicalName="java.net.SocketTest$ServerSendRecieveThread", simpleName="SocketTest$ServerSendRecieveThread");
		class ServerSendRecieveThread: public JThread{

		public:
			JString* ReachedString;
			JString *recieveBuffer;

			ServerSendRecieveThread() :
					JThread(), ReachedString(NULL), recieveBuffer(NULL){
			}

			~ServerSendRecieveThread(){
			}

			static JClass* getClazz();
			virtual void run(){
				try{
					JServerSocket* ServerSocket = new JServerSocket(5268);
					JSocket* ClientSocketOnServerThread = ServerSocket->accept();
					ClientSocketOnServerThread->setOOBInline(true);
					JObjectOutputStream* ServerSocketOut = new JObjectOutputStream(ClientSocketOnServerThread->getOutputStream());
					JBufferedReader *ServerSocketIn = new JBufferedReader(new JInputStreamReader(ClientSocketOnServerThread->getInputStream()));

					JString* testerString = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t,.;:!?[](){}!1234567890!@#$%^&*~-");

					ReachedString = ServerSocketIn->readLine();

					//ServerSocketOut->writeByte(105);
					ClientSocketOnServerThread->sendUrgentData(104);

					ServerSocketOut->flush();
					JPrimitiveByteArray *writeBuffer;

					writeBuffer = testerString->getBytes();
					ServerSocketOut->write(writeBuffer, 0, testerString->length());
					ServerSocketOut->flush();

					ClientSocketOnServerThread->setReceiveBufferSize(1000);

					recieveBuffer = ServerSocketIn->readLine();

					this->sleep(2000);

					ClientSocketOnServerThread->close();
					ServerSocket->close();

				} catch (JException* t1){
					JSystem::out->println((new JStringBuilder())->append("Exception Thrown Message: ")->append(t1->getMessage())->toString());

				} catch (...){
					JSystem::out->println(new JString("Unknown exception thrown"));
				}

			}

		};

		//@Class(canonicalName="java.net.SocketTest$ServerCloseSocketThread", simpleName="SocketTest$ServerCloseSocketThread");
		class ServerCloseSocketThread: public JThread{

		public:
			JException* outputClosedException;

			ServerCloseSocketThread() :
					JThread(), outputClosedException(NULL){
			}

			~ServerCloseSocketThread(){
			}

			static JClass* getClazz();
			virtual void run(){
				try{
					JServerSocket* ServerSocket = new JServerSocket(5269);
					JSocket* ClientSocketOnServerThread = ServerSocket->accept();
					ClientSocketOnServerThread->setOOBInline(true);
					JObjectOutputStream* ServerSocketOut = new JObjectOutputStream(ClientSocketOnServerThread->getOutputStream());
					JBufferedReader *ServerSocketIn = new JBufferedReader(new JInputStreamReader(ClientSocketOnServerThread->getInputStream()));

					JString str = ServerSocketIn->readLine();

					this->sleep(1000);

					ClientSocketOnServerThread->close();
					ServerSocket->close();
					ServerSocketOut->write(255);
					ServerSocketOut->flush();

				} catch (JException* t1){
					//JSystem::out->println((new JStringBuilder())->append("Exception Thrown Message: ")->append(t1->getMessage())->toString());
					outputClosedException = t1;

				} catch (...){
					JSystem::out->println(new JString("Unknown exception thrown"));
				}
			}

		};

		JSocketTest::JSocketTest() :
				JTestCase(getClazz(), new JString("test")){
			testerString = NULL;

		}

		JSocketTest::~JSocketTest(){
		}

		void JSocketTest::test(){

			testerString = new JString("the quick brown fox jumps over the lazy dog THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG\t,.;:!?[](){}!1234567890!@#$%^&*~-");

			ServerSendRecieveThread *serverSendRecieveThread = new ServerSendRecieveThread();
			ClientSendRecieveThread *clientSendRecieveThread = new ClientSendRecieveThread();
			ServerCloseSocketThread *serverCloseSocketThread = new ServerCloseSocketThread();
			ClientCloseSocketThread *clientCloseSocketThread = new ClientCloseSocketThread();

			serverSendRecieveThread->start();
			clientSendRecieveThread->start();
			serverCloseSocketThread->start();
			clientCloseSocketThread->start();

			serverSendRecieveThread->join();
			clientSendRecieveThread->join();
			serverCloseSocketThread->join();
			clientCloseSocketThread->join();

			JStringBuilder *stringBuilder = new JStringBuilder();
			for (jint i = 0; i < 10000; i++){
				stringBuilder->append("a");
			}

			assertEquals(testerString, serverSendRecieveThread->ReachedString);
			assertEquals(jbyte(104), clientSendRecieveThread->ackByte);
			assertEquals(testerString, clientSendRecieveThread->reachedString);
			assertEquals(stringBuilder->toString(), serverSendRecieveThread->recieveBuffer);
			assertEquals(true, clientSendRecieveThread->timeoutException->isInstanceOf(JSocketTimeoutException::getClazz()));

			assertEquals(true, clientCloseSocketThread->inputClosedException->isInstanceOf(JSocketException::getClazz()));
			assertEquals(true, clientCloseSocketThread->inputClosedException->getMessage()->contains(new JString("Socket is closed")));

			assertEquals(true, serverCloseSocketThread->outputClosedException->isInstanceOf(JSocketException::getClazz()));
			assertEquals(true, serverCloseSocketThread->outputClosedException->getMessage()->contains(new JString("Socket is closed")));

		}

	}
}
