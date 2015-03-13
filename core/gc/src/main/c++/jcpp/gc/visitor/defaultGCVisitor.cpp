#include "jcpp/gc/visitor/defaultGCVisitor.h"

namespace jcpp {
	namespace gc {
		namespace visitor {

			void defaultGCVisitor::startVisitClassInfo(ClassInfo *ci) {
			}

			void defaultGCVisitor::visitStaticFieldInfo(FieldInfo *fi) {
			}

			void defaultGCVisitor::endVisitClassInfo(ClassInfo *ci) {
			}

			void defaultGCVisitor::startVisitMethodCallInfo(MethodCallInfo *mi) {
			}

			void defaultGCVisitor::visitParameterInfo(ParameterInfo *pi) {
			}

			void defaultGCVisitor::visitVariableInfo(VariableInfo *vi) {
			}

			void defaultGCVisitor::endVisitMethodCallInfo(MethodCallInfo *mi) {
			}

			void defaultGCVisitor::startVisitObjectInfoGroup(ObjectInfoGroup *oi) {
			}

			void defaultGCVisitor::startVisitObjectInfo(ObjectInfo *oi) {
			}

			void defaultGCVisitor::visitFieldInfo(FieldInfo *fi) {
			}

			void defaultGCVisitor::endVisitObjectInfo(ObjectInfo *oi) {
			}

			void defaultGCVisitor::endVisitObjectInfoGroup(ObjectInfoGroup *oi) {
			}

			defaultGCVisitor::~defaultGCVisitor() {
			}

		}
	}
}
