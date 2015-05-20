#include "jcpp/gc/Heap.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {

		Heap* Heap::heap = null;

		Heap::Heap() :
				objectInfoGroupsByAddress(), classInfos(null), classInfosSize(0), classInfosCapacity(CLASSINFOS_START_SIZE), lastAddress(0), lastObjectInfoGroup(null){
			objectInfoGroupsMutex = NativeFactory::getNativeThreadFactory()->createNativeMutex();
			classInfosMutex = NativeFactory::getNativeThreadFactory()->createNativeMutex();
			classInfos = new ClassInfo*[CLASSINFOS_START_SIZE];
		}

		Heap* Heap::getHeap(){
			if (heap == null){
				heap = new Heap();
			}
			return heap;
		}

		void Heap::addCreatedObject(ObjectInfo* oi){
			objectInfoGroupsMutex->lock();

			jlong address = oi->getAddress();

			if (lastAddress == address){
				lastObjectInfoGroup->addObjectInfo(oi);
				objectInfoGroupsMutex->unlock();
				return;
			}

			ObjectInfoGroup* objectInfoGroup = objectInfoGroupsByAddress[address];
			if (objectInfoGroup == null){
				objectInfoGroup = new ObjectInfoGroup(address);
				objectInfoGroupsByAddress[address] = objectInfoGroup;
			}
			objectInfoGroup->addObjectInfo(oi);

			lastAddress = address;
			lastObjectInfoGroup = objectInfoGroup;

			objectInfoGroupsMutex->unlock();
		}

		void Heap::addClassInfo(ClassInfo* ci){

			classInfosMutex->lock();

			if (classInfosSize == classInfosCapacity){
				ClassInfo** newClassInfos = new ClassInfo*[classInfosCapacity + CLASSINFOS_SIZE_INCREMENT];
				for (jint i = 0; i < classInfosSize; i++){
					newClassInfos[i] = classInfos[i];
				}
				delete[] classInfos;
				classInfos = newClassInfos;
				classInfosCapacity += CLASSINFOS_SIZE_INCREMENT;
			}
			classInfos[classInfosSize++] = ci;

			classInfosMutex->unlock();
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Heap::addRoot(TraverseContext* context){
			for (jint index = 0; index < classInfosSize; index++){
				context->addClassInfo(classInfos[index]);
			}
		}

		void Heap::removeObjectsToBeDeleted(std::set<jlong>* addresses){
			ScopedLock sync(*objectInfoGroupsMutex);

			lastAddress = 0;
			lastObjectInfoGroup = null;

			for (std::set<jlong>::iterator it = addresses->begin(); it != addresses->end(); it++){
				ObjectInfoGroup* objectInfoGroup = objectInfoGroupsByAddress[*it];
				if (objectInfoGroup){
					delete objectInfoGroup;
				}
				objectInfoGroupsByAddress.erase(*it);
			}
		}

		/**
		 * Note: Do not synchronize the below method because we might have a dead lock between a suspended thread and the GC Thread
		 */
		void Heap::getAllObjectAddresses(std::set<jlong>& addresses){
			for (std::map<jlong, ObjectInfoGroup*>::iterator it = objectInfoGroupsByAddress.begin(); it != objectInfoGroupsByAddress.end(); ++it){
				addresses.insert(it->first);
			}
		}

		ObjectInfoGroup* Heap::getObjectInfoGroupFromAddress(jlong address){
			ScopedLock sync(*objectInfoGroupsMutex);
			return objectInfoGroupsByAddress[address];
		}

		Heap::~Heap(){
			delete objectInfoGroupsMutex;
			delete classInfosMutex;
			delete classInfos;
		}

		void Heap::acceptObjectInfoGroupVisitor(IObjectInfoGroupVisitor *v){

			ObjectInfoGroup* oig;

			ObjectInfo** oi;
			jint oiSize;

			FieldInfo** fi;
			jint fiSize;
			std::set<jlong> addresses;
			getAllObjectAddresses(addresses);
			int i = 0;
			for (std::set<jlong>::iterator it = addresses.begin(); it != addresses.end(); it++){

				jlong address = *it;
				oig = getObjectInfoGroupFromAddress(address);
				v->startVisitObjectInfoGroup(oig);

				oi = oig->getObjectInfos();
				oiSize = oig->getSize();

				for (jint oiIndex = 0; oiIndex < oiSize; oiIndex++){
					v->startVisitObjectInfo(oi[oiIndex]);
					fi = oi[oiIndex]->getFieldInfos();
					fiSize = oi[oiIndex]->getFieldCount();
					for (jint fiIdx = 0; fiIdx < fiSize; fiIdx++){
						v->visitFieldInfo(fi[fiIdx]);
					}
					v->endVisitObjectInfo(oi[oiIndex]);


				}
				i++;
				v->endVisitObjectInfoGroup(oig);
			}
		}

		void Heap::acceptClassInfoVisitor(IClassInfoVisitor *v){

			FieldInfo** sfi;
			jint sfiSize;

			for (jint ciIdx = 0; ciIdx < classInfosSize; ciIdx++){
				v->startVisitClassInfo(classInfos[ciIdx]);
				sfi = classInfos[ciIdx]->getStaticFieldInfos();
				sfiSize = classInfos[ciIdx]->getStaticFieldCount();
				for (jint sfiIdx = 0; sfiIdx < sfiSize; sfiIdx++){
					v->visitStaticFieldInfo(sfi[sfiIdx]);
				}
				v->endVisitClassInfo(classInfos[ciIdx]);

			}

		}

	}
}
