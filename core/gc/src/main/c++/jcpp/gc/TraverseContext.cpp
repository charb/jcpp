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
					jint fieldCount = (*it)->getFieldCount();
					if(fieldCount > 0) {
						addFieldInfos(fieldCount, (*it)->getFieldInfos());
					}
				}
			}
		}

		void TraverseContext::addClassInfo(ClassInfo* ci) {
			jint fieldCount = ci->getStaticFieldCount();
			if(fieldCount > 0) {
				addFieldInfos(fieldCount, ci->getStaticFieldInfos());
			}
		}

		void TraverseContext::addMethodCallInfo(MethodCallInfo* mci) {
			ObjectInfo* oi = mci->getObjectInfo();
			if(oi) {
				addObjectInfoGroup(heap->getObjectInfoGroupFromAddress(oi->getAddress()));
			}

			jint parameterCount = mci->getParameterCount();
			if(parameterCount > 0) {
				ParameterInfo** parameterInfos = mci->getParameterInfos();
				for(jint parameterIndex = 0; parameterIndex < parameterCount; parameterIndex++) {
					if(parameterInfos[parameterIndex]) {
						addPointerInfo(dynamic_cast<PointerInfo*>(parameterInfos[parameterIndex]));
					}
				}
			}

			jint variableCount = mci->getVariableCount();
			if(variableCount > 0) {
				VariableInfo** variableInfos = mci->geVariableInfos();
				for(jint variableIndex = 0; variableIndex < variableCount; variableIndex++) {
					if(variableInfos[variableIndex]) {
						addPointerInfo(dynamic_cast<PointerInfo*>(variableInfos[variableIndex]));
					}
				}
			}
		}

		std::set<jlong>* TraverseContext::getTraversedAddresses() {
			return &done;
		}

		std::set<jlong>* TraverseContext::getUnMarkedAddresses() {
			return &all;
		}

		void TraverseContext::addFieldInfos(jint count, FieldInfo** fieldInfos) {
			for(jint fieldInfoIndex = 0; fieldInfoIndex < count; fieldInfoIndex++) {
				if(fieldInfos[fieldInfoIndex]) {
					addPointerInfo(fieldInfos[fieldInfoIndex]);
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
