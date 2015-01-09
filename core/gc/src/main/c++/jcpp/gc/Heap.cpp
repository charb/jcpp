#include "jcpp/gc/Heap.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		Heap* Heap::heap = null;

		Heap::Heap() : objectInfoGroupsByAddress(), classInfos() {
			objectInfoGroupsMutex = NativeFactory::getNativeThreadFactory()->createNativeMutex();
			classInfosMutex  = NativeFactory::getNativeThreadFactory()->createNativeMutex();
		}

		Heap* Heap::getHeap() {
			if(heap == null) {
				heap = new Heap();
			}
			return heap;
		}

		void Heap::addCreatedObject(ObjectInfo* oi) {
			ScopedLock sync(*objectInfoGroupsMutex);

			jlong address = oi->getAddress();
			ObjectInfoGroup* objectInfoGroup = objectInfoGroupsByAddress[address];
			if(objectInfoGroup == null) {
				objectInfoGroup = new ObjectInfoGroup(address);
				objectInfoGroupsByAddress[address] = objectInfoGroup;
			}
			objectInfoGroup->addObjectInfo(oi);
		}

		void Heap::addClassInfo(ClassInfo* ci) {
			ScopedLock sync(*classInfosMutex);
			classInfos.push_back(ci);
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Heap::addRoot(TraverseContext* context) {
			for(std::vector<ClassInfo*>::iterator it = classInfos.begin(); it != classInfos.end(); it++) {
				context->addClassInfo(*it);
			}
		}

		void Heap::removeObjectsToBeDeleted(std::set<jlong>* addresses) {
			ScopedLock sync(*objectInfoGroupsMutex);
			for(std::set<jlong>::iterator it = addresses->begin(); it != addresses->end(); it++) {
				ObjectInfoGroup* objectInfoGroup = objectInfoGroupsByAddress[*it];
				if(objectInfoGroup) {
					delete objectInfoGroup;
				}
				objectInfoGroupsByAddress.erase(*it);
			}
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Heap::getAllObjectAddresses(std::set<jlong>& addresses) {
			for (std::map<jlong, ObjectInfoGroup*>::iterator it = objectInfoGroupsByAddress.begin(); it != objectInfoGroupsByAddress.end(); ++it) {
				addresses.insert(it->first);
			}
		}

		ObjectInfoGroup* Heap::getObjectInfoGroupFromAddress(jlong address) {
			ScopedLock sync(*objectInfoGroupsMutex);
			return objectInfoGroupsByAddress[address];
		}

		Heap::~Heap() {
			delete objectInfoGroupsMutex;
			delete classInfosMutex;
		}

	}
}
