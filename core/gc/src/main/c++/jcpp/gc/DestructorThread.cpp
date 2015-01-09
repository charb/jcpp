#include "jcpp/gc/DestructorThread.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/gc/Finalizable.h"
#include "jcpp/gc/GarbageCollector.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		DestructorThread::DestructorThread(Heap* heap) : heap(heap), addressSetsToDestroy(), shutdownFlagged(false), conditionNotified(false) {
			NativeThreadFactory* threadFactory = NativeFactory::getNativeThreadFactory();
			setsMutex = threadFactory->createNativeMutex();
			conditionMutex = threadFactory->createNativeMutex();
			condition = threadFactory->createNativeCondition(conditionMutex);
			nativeThread = threadFactory->createNativeThread(this);
			NativeString threadName("Destructor Thread");
			nativeThread->setName(threadName);
		}

		NativeThread* DestructorThread::getNativeThread() {
			return nativeThread;
		}

		void DestructorThread::destroy(std::set<jlong>* addressesToDelete) {
			heap->removeObjectsToBeDeleted(addressesToDelete);

			for(std::set<jlong>::iterator it = addressesToDelete->begin(); it != addressesToDelete->end(); it++) {
				Finalizable* pointer = (Finalizable*)(*it);
				try {
					pointer->finalize();
				} catch(...) {
				}
				delete pointer;
			}

			delete addressesToDelete;
			addressesToDelete = null;
		}

		void DestructorThread::addSetToDestroy(std::set<jlong>* addressesToDelete) {
			setsMutex->lock();
			addressSetsToDestroy.push(addressesToDelete);
			setsMutex->unlock();

			conditionMutex->lock();
			conditionNotified = true;
			condition->notifyAll();
			conditionMutex->unlock();
		}

		void DestructorThread::start() {
			if(nativeThread->getState() == NTH_NEW) {
				nativeThread->start();
			}
		}

		void DestructorThread::shutdown() {
			conditionMutex->lock();
			shutdownFlagged = true;
			condition->notifyAll();
			conditionMutex->unlock();
		}

		void DestructorThread::run() {
			jbool isShutdownFlagged = false;
			jbool callGC = false;
			while(!isShutdownFlagged) {

				int size = 0;
				std::set<jlong>* addressesToDelete = null;
				do {
					setsMutex->lock();
					size = addressSetsToDestroy.size();
					if(size > 0) {
						size--;
						addressesToDelete = addressSetsToDestroy.front();
						addressSetsToDestroy.pop();
					}
					setsMutex->unlock();
					if(addressesToDelete != null) {
						destroy(addressesToDelete);
						addressesToDelete = null;
					}
				} while(size > 0);

				conditionMutex->lock();
				try {
					condition->wait(60 * 1000);
				} catch(NativeException& ne) {
				}
				isShutdownFlagged = shutdownFlagged;
				if(!isShutdownFlagged && !conditionNotified) {
					callGC = true;
				}
				conditionMutex->unlock();

				if(callGC) {
					callGC = false;
					GarbageCollector::getGarbageCollector()->gc();
					conditionNotified = false;
				}
			}
		}

		DestructorThread::~DestructorThread() {
			delete conditionMutex;
			delete setsMutex;
			delete condition;
			delete nativeThread;
		}

	}
}
