#include "jcpp/gc/TraverseContext.h"
#include "jcpp/gc/Heap.h"

namespace jcpp {
	namespace gc {

		TraverseContext::TraverseContext(Heap* heap) : all(), done(), heap(heap) {
			heap->getAllObjectAddresses(all);
		}

		void TraverseContext::addObjectInfoGroup(ObjectInfoGroup* oig) {
			if(oig && !isDone(oig)) {
				jlong address = oig->getAddress();
				done.insert(address);
				all.erase(address);

				std::vector<ObjectInfo*>* objectInfos = oig->getObjectInfos();
				for(std::vector<ObjectInfo*>::iterator it = objectInfos->begin(); it != objectInfos->end(); it++) {
					addFieldInfos((*it)->getFieldInfos());
				}
			}
		}

		void TraverseContext::addClassInfo(ClassInfo* ci) {
			addFieldInfos(ci->getStaticFieldInfos());
		}

		void TraverseContext::addMethodCallInfo(MethodCallInfo* mci) {
			ObjectInfo* oi = mci->getObjectInfo();
			if(oi) {
				addObjectInfoGroup(heap->getObjectInfoGroupFromAddress(oi->getAddress()));
			}

			std::vector<ParameterInfo*>* parameterInfos = mci->getParameterInfos();
			if(parameterInfos->size() > 0) {
				for(std::vector<ParameterInfo*>::iterator it = parameterInfos->begin(); it != parameterInfos->end(); it++) {
					addPointerInfo(*it);
				}
			}

			std::vector<VariableInfo*>* variableInfos = mci->geVariableInfos();
			if(variableInfos->size() > 0) {
				for(std::vector<VariableInfo*>::iterator it = variableInfos->begin(); it != variableInfos->end(); it++) {
					addPointerInfo(*it);
				}
			}
		}

		std::set<jlong>* TraverseContext::getTraversedAddresses() {
			return &done;
		}

		std::set<jlong>* TraverseContext::getUnMarkedAddresses() {
			return &all;
		}

		void TraverseContext::addFieldInfos(std::vector<FieldInfo*>* fieldInfos) {
			if(fieldInfos->size() > 0) {
				for(std::vector<FieldInfo*>::iterator it = fieldInfos->begin(); it != fieldInfos->end(); it++) {
					addPointerInfo(*it);
				}
			}
		}

		void TraverseContext::addPointerInfo(PointerInfo* pointerInfo) {
			jlong address = pointerInfo->getPointedToAddress();
			if(address) {
				addObjectInfoGroup(heap->getObjectInfoGroupFromAddress(address));
			}
		}

		jbool TraverseContext::isDone(ObjectInfoGroup* oig) {
			return done.find(oig->getAddress()) != done.end();
		}

		TraverseContext::~TraverseContext() {
		}

	}
}
