#include "jcpp/gc/GarbageCollector.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		GarbageCollector* GarbageCollector::garbageCollector = null;

		GarbageCollector::GarbageCollector() : heap(Heap::getHeap()), stack(Stack::getStack()), destructorThread(new DestructorThread(heap)), lastContext(null) {
			mutex = NativeFactory::getNativeThreadFactory()->createNativeMutex();
			destructorThread->start();
		}

		GarbageCollector* GarbageCollector::getGarbageCollector() {
			if(garbageCollector == null) {
				garbageCollector = new GarbageCollector();
			}
			return garbageCollector;
		}

		void GarbageCollector::gc() {
			ScopedLock sync(*mutex);

			std::vector<NativeThread *> threads;
			NativeFactory::getNativeThreadFactory()->getAllThreads(threads);

			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();
			NativeThread* destructorNativeThread = destructorThread->getNativeThread();

			std::vector<NativeThread *>::iterator it = threads.begin();
			while(it != threads.end()) {
				if(((*it) == currentThread) || ((*it) == destructorNativeThread)) {
					it = threads.erase(it);
				} else if((*it)->isRunning()) {
					(*it)->suspend();
					it++;
				} else {
					it = threads.erase(it);
				}
			}

			TraverseContext* context = new TraverseContext(heap);
			heap->addRoot(context);
			stack->addRoot(context);

			for (std::vector<NativeThread *>::iterator it = threads.begin(); it != threads.end(); it++){
				(*it)->resume();
			}

			if (lastContext){
				std::set<jlong>* lastUnMarkedAddresses = lastContext->getUnMarkedAddresses();
				std::set<jlong>* currentUnMarkedAddresses = context->getUnMarkedAddresses();
				std::set<jlong>* addressesToDelete = new std::set<jlong>();

				for(std::set<jlong>::iterator it = lastUnMarkedAddresses->begin(); it != lastUnMarkedAddresses->end(); it++) {
					if(currentUnMarkedAddresses->find(*it) != currentUnMarkedAddresses->end()) {
						addressesToDelete->insert(*it);
					}
				}

				delete lastContext;
				lastContext = null;

				destructorThread->addSetToDestroy(addressesToDelete);
			}

			lastContext = context;
		}

		void GarbageCollector::acceptGCVisitor(IGCVisitor *visitor){
			acceptVisitor(visitor,visitor,visitor);
		}

		void GarbageCollector::acceptClassVisitor(IClassInfoVisitor *visitor){
			acceptVisitor(visitor,null,null);
		}

		void GarbageCollector::acceptObjectVisitor(IObjectInfoGroupVisitor *visitor){
			acceptVisitor(null,visitor,null);
		}

		void GarbageCollector::acceptMethodCallVisitor(IMethodCallVisitor *visitor){
			acceptVisitor(null, null, visitor);
		}

		void GarbageCollector::acceptVisitor(IClassInfoVisitor *classVisitor, IObjectInfoGroupVisitor * objectInfoGroupVisitor, IMethodCallVisitor *methodCallVisitor){

			std::vector<NativeThread *> threads;

			NativeFactory::getNativeThreadFactory()->getAllThreads(threads);
			NativeThread* currentThread = NativeFactory::getNativeThreadFactory()->currentThread();
			NativeThread* destructorNativeThread = destructorThread->getNativeThread();
			std::vector<NativeThread *>::iterator it = threads.begin();
			while (it != threads.end()){
				if (((*it) == currentThread) || ((*it) == destructorNativeThread)){
					it = threads.erase(it);
				} else if ((*it)->isRunning()){
					(*it)->suspend();
					it++;
				} else {
					it = threads.erase(it);
				}
			}


			if(classVisitor) {
				heap->acceptClassInfoVisitor(classVisitor);
			}
			if(objectInfoGroupVisitor) {
				heap->acceptObjectInfoGroupVisitor(objectInfoGroupVisitor);
			}
			if(methodCallVisitor)
			{
				stack->acceptMethodCallVisitor(methodCallVisitor);
			}


			for (std::vector<NativeThread *>::iterator it = threads.begin(); it != threads.end(); it++){
				(*it)->resume();
			}

		}

		GarbageCollector::~GarbageCollector() {
			if(destructorThread != null) {
				delete destructorThread;
				destructorThread = null;
			}
			delete mutex;
		}

	}
}
