#include "NativeTestUtils.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"

#include <iostream>

#define TEST_NAME "Native Socket"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;
using namespace jcpp::native::api::net;
using namespace jcpp::native::api::nthread;

#define CHECK(R,E,PM,EM,ID) if(R == E) { logInfo(PM); } else { logError(EM); testsPassed = false;}
#define CHECK_TRUE(R,PM,EM,ID) if(R) { logInfo(PM); } else { logError(EM); testsPassed = false;}

#define CHECK_EM(R,E,EM,ID) if(R == E) { } else { logError(EM), testsPassed = false;}
#define CHECK_TRUE_EM(R,EM,ID) if(R) { } else { logError(EM); testsPassed = false;}

#define CHECK_FE(R,E,PM,EM,ID) if(R == E) { logInfo(PM); } else { logError(EM); testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }
#define CHECK_TRUE_FE(R,PM,EM,ID) if(R) { logInfo(PM); } else { logError(EM); testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }

#define CHECK_EM_FE(R,E,EM,ID) if(R == E) { } else { logError(EM), testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }
#define CHECK_TRUE_EM_FE(R,EM,ID) if(R) { } else { logError(EM); testsPassed = false; logSection("Exiting Runnable id = %d [FAILED]", ID); return; }

// TODO A test to send large data size in one write method call to check if Large message size is thrown > 200 KB Size

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Server Client Socket Runnable
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ServerClientSocketRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeSocket * socket;

	ServerClientSocketRunnable(int id, NativeSocket * serverClientSocket) :
			NativeRunnable(), id(id), testsPassed(true), socket(serverClientSocket) {
	}

	virtual ~ServerClientSocketRunnable() {
	}

	virtual void run() {
		logSection("Starting Server Client Runnable id = %d", id);

		try {
			NativeSystem * system = NativeFactory::getNativeSystem();

			NativeInetSocketAddress localSocketAddress = socket->getLocalSocketAddress();
			logInfo("Server Client Socket id=%d Local Socket Inet Address after connection: host = %s port = %d", id, localSocketAddress.getHost().getHostName().getString().c_str(), localSocketAddress.getPort());

			NativeInetSocketAddress remoteSocketAddress = socket->getRemoteSocketAddress();
			logInfo("Server Client Socket id=%d Remote Socket Inet Address after connection: host = %s port = %d", id, remoteSocketAddress.getHost().getHostName().getString().c_str(), remoteSocketAddress.getPort());

			NativeInputStream* inputStream = socket->getInputStream();
			CHECK_TRUE(inputStream, "Tested getting server client socket input Stream", "Failed to get the Server Client Socket's input stream", id);

			NativeOutputStream* outputStream = socket->getOutputStream();
			CHECK_TRUE(outputStream, "Tested getting server client socket output Stream", "Failed to get the Server Client Socket's output stream", id);

			if (testsPassed) {
				jint timeout = 1000;
				logInfo("Setting the Server Client Socket id = %d Timeout to %d millis", id, timeout);
				socket->setSoTimeout(timeout);

				try {
					outputStream->write(25);
					logInfo("Successfully wrote one byte of data into the server client socket output stream id = %d", id);

					jbyte value = inputStream->read();
					CHECK(value, 50, "Read a single byte successfully from the server client socket input stream", "An unexpected byte value was read from the server client socket input stream", id);
				} catch (NativeException& e) {
					testsPassed = false;
					logError("NativeException thrown in Server Client Socket while reading from the socket input stream, Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
							e.getMessage().getString().c_str(), e.getErrorCode());
				} catch (...) {
					testsPassed = false;
					logError("Exception thrown in Server Client Socket while reading from the socket input stream, Runnable id = %d", id);
				}

			}

			try {
				logInfo("Closing Server Client Socket...");
				socket->close();
			} catch (NativeException& e) {
				testsPassed = false;
				logError("NativeException thrown in Server Client Socket while closing client Socket, Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
						e.getMessage().getString().c_str(), e.getErrorCode());
			} catch (...) {
				testsPassed = false;
				logError("Exception thrown in Server Client Socket while closing client Socket, Runnable id = %d", id);
			}
			delete socket;
			socket = null;

		} catch (NativeException& e1) {
			testsPassed = false;
			logError("NativeException thrown in Server Client Socket Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e1.getClassName().getString().c_str(), e1.getMethodName().getString().c_str(), e1.getMessage().getString().c_str());
		} catch (...) {
			testsPassed = false;
			logError("Exception thrown in Server Client Socket Runnable id = %d", id);
		}

		if (testsPassed) {
			logSection("Exiting Server Client Runnable id = %d [PASSED]", id);
		} else {
			logSection("Exiting Server Client Runnable id = %d [FAILED]", id);
		}
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Server Socket Runnable
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ServerSocketRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeCondition * condition;
	jint port;
	jbool stop;
	jint clientCount;

	ServerSocketRunnable(int id, NativeCondition * condition, jint clientCount, jint port) :
			NativeRunnable(), id(id), testsPassed(true), condition(condition), port(port), stop(false), clientCount(clientCount) {
	}

	virtual ~ServerSocketRunnable() {
	}

	virtual void run() {
		logSection("Starting Server Runnable id = %d", id);

		try {

			NativeSystem * system = NativeFactory::getNativeSystem();
			NativeNetFactory * netFactory = NativeFactory::getNativeNetFactory();
			NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

			NativeServerSocket * serverSocket = netFactory->createNativeServerSocket();
			CHECK_TRUE_FE(serverSocket, "Tested creating a Server Socket", "Failed to create a Server Socket", id);

			serverSocket->bind(NativeInetSocketAddress(netFactory->getLocalHost(), port));
			logInfo("Binded Successfully the Server Socket to the local socket Address");

			NativeInetSocketAddress localSocketAddress = serverSocket->getLocalSocketAddress();
			port = localSocketAddress.getPort();
			logInfo("Server Socket id=%d Local Socket Inet Address after binding: host = %s port = %d", id, localSocketAddress.getHost().getHostName().getString().c_str(), port);

			jint timeout = 5000;
			logInfo("Setting the Server Socket Timeout to %d millis", timeout);
			serverSocket->setSoTimeout(timeout);

			condition->getMutex()->lock();
			condition->notifyAll();
			condition->getMutex()->unlock();

			jint exceptionCount = 0;
			jint connectionCount = 0;

			std::vector<ServerClientSocketRunnable *> clientRunnables;
			std::vector<NativeThread *> clientThreads;

			while (connectionCount != clientCount) {
				NativeSocket * clientSocket = null;

				jlong startTime = system->currentTimeMillis();
				jlong endTime = 0;
				try {
					logInfo("Calling Server Socket Accept method...");
					clientSocket = serverSocket->accept();
					endTime = system->currentTimeMillis();
					CHECK_TRUE(clientSocket, "Accepted successfully a client connection", "Accept method return null for a client connection", id);
					connectionCount++;
				} catch (NativeException& e) {
					if (++exceptionCount) {
						if (exceptionCount == 2) {
							logError("Server Failed to accept client connections for %d times in the timeout limit. Accept loop will be exited", exceptionCount);
							testsPassed = false;
							break;
						}
					}
					endTime = system->currentTimeMillis();
					logInfo("Failed to accept in server socket id = %d. Elapsed Time = %lld millis", id, (endTime - startTime));
					logError("NativeException thrown in Socket Server Runnable while accepting a client connection id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
							e.getMessage().getString().c_str(), e.getErrorCode());
					continue;
				}
				logInfo("Accept Method took %lld millis in Server Socket Runnable Id = %d \n", (endTime - startTime), id);

				ServerClientSocketRunnable * runnable = new ServerClientSocketRunnable(100 + connectionCount, clientSocket);
				NativeThread * thread = threadFactory->createNativeThread(runnable);

				clientRunnables.push_back(runnable);
				clientThreads.push_back(thread);

				thread->start();
			}

			threadFactory->currentThread()->sleep(1000);

			for (std::vector<NativeThread *>::iterator it = clientThreads.begin(); it != clientThreads.end(); ++it) {
				(*it)->join();
			}
			for (std::vector<ServerClientSocketRunnable *>::iterator it = clientRunnables.begin(); it != clientRunnables.end(); ++it) {
				if (!(*it)->testsPassed) {
					testsPassed = false;
				}
				delete *it;
			}
			clientRunnables.clear();

			try {
				serverSocket->close();
			} catch (NativeException& e) {
				testsPassed = false;
				logError("NativeException thrown in Socket Server while closing the Socket, Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
						e.getMessage().getString().c_str(), e.getErrorCode());
			} catch (...) {
				testsPassed = false;
				logError("Exception thrown in Socket Server while closing the Socket, Runnable id = %d", id);
			}
			delete serverSocket;
			serverSocket = null;

		} catch (NativeException& e1) {
			testsPassed = false;
			logError("NativeException thrown in Socket Server Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e1.getClassName().getString().c_str(), e1.getMethodName().getString().c_str(), e1.getMessage().getString().c_str());
		} catch (...) {
			testsPassed = false;
			logError("Exception thrown in Socket Server Runnable id = %d", id);
		}

		if (testsPassed) {
			logSection("Exiting Runnable id = %d [PASSED]", id);
		} else {
			logSection("Exiting Runnable id = %d [FAILED]", id);
		}
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Client Socket Runnable
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ClientSocketRunnable: public NativeRunnable {
public:

	jint id;
	jbool testsPassed;
	NativeCondition * condition;
	ServerSocketRunnable * serverSocketRunnable;

	ClientSocketRunnable(int id, NativeCondition * condition, ServerSocketRunnable * serverSocketRunnable) :
			NativeRunnable(), id(id), testsPassed(true), condition(condition), serverSocketRunnable(serverSocketRunnable) {
	}

	virtual ~ClientSocketRunnable() {
	}

	virtual void run() {
		logSection("Starting Client Runnable id = %d", id);

		try {

			NativeSystem * system = NativeFactory::getNativeSystem();
			NativeNetFactory * netFactory = NativeFactory::getNativeNetFactory();
			NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

			condition->getMutex()->lock();
			condition->wait(5000);
			condition->getMutex()->unlock();

			threadFactory->currentThread()->sleep(1000);

			CHECK_TRUE_EM_FE(serverSocketRunnable->port > 0, "Server Socket Port is not initialized, Client Socket will not be created", id);

			NativeSocket * socket = netFactory->createNativeSocket();
			CHECK_TRUE_FE(socket, "Tested creating a client Socket", "Failed to create a Client Socket", id);
			socket->bind(NativeInetSocketAddress(netFactory->getLocalHost(), 0));
			logInfo("Successfully binded the client socket id = %d to the local address", id);

			NativeInetSocketAddress localSocketAddress = socket->getLocalSocketAddress();
			logInfo("Client Socket id=%d Local Socket Inet Address after binding: host = %s port = %d", id, localSocketAddress.getHost().getHostName().getString().c_str(), localSocketAddress.getPort());
			NativeInetSocketAddress remoteSocketAddress = socket->getRemoteSocketAddress();
			logInfo("Client Socket id=%d Remote Socket Inet Address after binding: host = %s port = %d", id, remoteSocketAddress.getHost().getHostName().getString().c_str(), remoteSocketAddress.getPort());

			jlong connectST = system->currentTimeMillis();
			jlong connectET = 0;
			try {
				socket->connect(NativeInetSocketAddress(netFactory->getLocalHost(), serverSocketRunnable->port), 1000);
				connectET = system->currentTimeMillis();
				logInfo("Successfully connected the client socket id = %d to the server socket in %lld millis", id, (connectET - connectST));
			} catch (NativeException& e) {
				connectET = system->currentTimeMillis();
				logInfo("Failed to connect in client socket id = %d. Elapsed Time = %lld millis", id, (connectET - connectST));
				testsPassed = false;
				logError("NativeException thrown in Client Socket Runnable while connecting to the Server Socket id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
						e.getMessage().getString().c_str(), e.getErrorCode());
			}

			if (testsPassed) {
				NativeInputStream* inputStream = socket->getInputStream();
				CHECK_TRUE(inputStream, "Tested getting client socket input Stream", "Failed to get the Client Socket's input stream", id);

				NativeOutputStream* outputStream = socket->getOutputStream();
				CHECK_TRUE(outputStream, "Tested getting client socket output Stream", "Failed to get the Client Socket's output stream", id);

				if (testsPassed) {
					jint timeout = 1000;
					logInfo("Setting the Client Socket id = %d Timeout to %d millis", id, timeout);
					socket->setSoTimeout(timeout);

					jlong readST = system->currentTimeMillis();
					jlong readET = 0;
					try {
						jbyte value = inputStream->read();
						CHECK(value, 25, "Read a single byte successfully from the client socket input stream", "An unexpected byte value was read from the client socket input stream", id);
						readET = system->currentTimeMillis();
						logInfo("Reading the single byte in client socket id = %d took %lld millis", id, (readET - readST));

						outputStream->write(50);
						logInfo("Successfully wrote one byte of data into the client socket output stream id = %d", id);
					} catch (NativeException& e) {
						readET = system->currentTimeMillis();
						logInfo("Failed to communicate in client socket id = %d. Elapsed Time = %lld millis", id, (readET - readST));

						testsPassed = false;
						logError("NativeException thrown in Client Socket while reading from the socket input stream, Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
								e.getMessage().getString().c_str(), e.getErrorCode());
					} catch (...) {
						testsPassed = false;
						logError("Exception thrown in Client Socket while reading from the socket input stream, Runnable id = %d", id);
					}

				}
			}

			try {
				logInfo("Closing Client socket with id = %d", id);
				socket->close();
			} catch (NativeException& e) {
				testsPassed = false;
				logError("NativeException thrown in Client Socket while closing the Socket, Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(),
						e.getMessage().getString().c_str(), e.getErrorCode());
			} catch (...) {
				testsPassed = false;
				logError("Exception thrown in Client Socket while closing the Socket, Runnable id = %d", id);
			}
			delete socket;
			socket = null;

		} catch (NativeException& e1) {
			testsPassed = false;
			logError("NativeException thrown in Socket Client Runnable id = %d Class = %s Method = %s Message = %s Error Code = %d", id, e1.getClassName().getString().c_str(), e1.getMethodName().getString().c_str(), e1.getMessage().getString().c_str());
		} catch (...) {
			testsPassed = false;
			logError("Exception thrown in Socket Client Runnable id = %d", id);
		}

		if (testsPassed) {
			logSection("Exiting Runnable id = %d [PASSED]", id);
		} else {
			logSection("Exiting Runnable id = %d [FAILED]", id);
		}
	}

};

//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//~ Main Method
//~-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	logTitle(TEST_NAME);

	try {

		jbool testsPassed = true;

		NativeSystem * system = NativeFactory::getNativeSystem();
		NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();

		NativeMutex * conditionMutex = threadFactory->createNativeMutex();
		NativeCondition * condition = threadFactory->createNativeCondition(conditionMutex);

		jint clientsCount = 5;

		ServerSocketRunnable * serverSocketRunnable = new ServerSocketRunnable(0, condition, clientsCount, 0);
		NativeThread * serverSocketThread = threadFactory->createNativeThread(serverSocketRunnable);

		std::vector<ClientSocketRunnable *> clientRunnables;
		std::vector<NativeThread *> clientThreads;

		jint i = 0;
		for (i = 0; i < clientsCount; i++) {
			ClientSocketRunnable * clientSocketRunnable = new ClientSocketRunnable(1 + i, condition, serverSocketRunnable);
			NativeThread * clientSocketThread = threadFactory->createNativeThread(clientSocketRunnable);

			clientRunnables.push_back(clientSocketRunnable);
			clientThreads.push_back(clientSocketThread);

			clientSocketThread->start();
		}

		threadFactory->currentThread()->sleep(1000);

		serverSocketThread->start();

		serverSocketThread->join();
		if (!serverSocketRunnable->testsPassed) {
			testsPassed = false;
			delete serverSocketThread;
			serverSocketThread = null;
		}

		for (std::vector<NativeThread *>::iterator it = clientThreads.begin(); it != clientThreads.end(); ++it) {
			(*it)->join();
		}
		for (std::vector<ClientSocketRunnable *>::iterator it = clientRunnables.begin(); it != clientRunnables.end(); ++it) {
			if (!(*it)->testsPassed) {
				testsPassed = false;
			}
			delete *it;
		}
		clientRunnables.clear();

		if (!testsPassed) {
			FAIL_TEST(TEST_NAME)
		}

		delete condition;
		delete conditionMutex;

	} catch (NativeException& e) {
		logError("NativeException thrown Class = %s Method = %s Message = %s Error Code = %d", e.getClassName().getString().c_str(), e.getMethodName().getString().c_str(), e.getMessage().getString().c_str(), e.getErrorCode());
		FAIL_TEST(TEST_NAME)
	} catch (...) {
		logError("Exception thrown in Main Method !");
		FAIL_TEST(TEST_NAME)
	}

	PASS_TEST(TEST_NAME)
}
