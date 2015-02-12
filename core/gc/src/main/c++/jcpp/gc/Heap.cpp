#include "jcpp/gc/Heap.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		Heap* Heap::heap = null;

		Heap::Heap() : objectInfoGroupsByAddress(), classInfos(null), classInfosSize(0), classInfosCapacity(CLASSINFOS_START_SIZE) {
			objectInfoGroupsMutex = NativeFactory::getNativeThreadFactory()->createNativeMutex();
			classInfosMutex  = NativeFactory::getNativeThreadFactory()->createNativeMutex();
			classInfos = new ClassInfo*[CLASSINFOS_START_SIZE];
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
			if(classInfosSize == classInfosCapacity) {
				ClassInfo** newClassInfos = new ClassInfo*[classInfosCapacity + CLASSINFOS_SIZE_INCREMENT];
				for(jint i = 0; i < classInfosSize; i++) {
					newClassInfos[i] = classInfos[i];
				}
				delete [] classInfos;
				classInfos = newClassInfos;
				classInfosCapacity += CLASSINFOS_SIZE_INCREMENT;
			}
			classInfos[classInfosSize++] = ci;
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Heap::addRoot(TraverseContext* context) {
			for(jint index = 0; index < classInfosSize; index++) {
				context->addClassInfo(classInfos[index]);
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
			delete classInfos;
		}

	}
}
