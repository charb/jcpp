#ifndef JCPP_GC_DefaULTGCVISITOR_H
#define JCPP_GC_DefaULTGCVISITOR_H

#include "jcpp/gc/visitor/IGCVisitor.h"

namespace jcpp {
	namespace gc {
		namespace visitor {

			class DefaultGCVisitor : public IGCVisitor{
				public:
					virtual void startVisitClassInfo(ClassInfo *ci);
					virtual void visitStaticFieldInfo(FieldInfo *fi);
					virtual void endVisitClassInfo(ClassInfo *ci);

					virtual void startVisitMethodCallInfo(MethodCallInfo *mi);
					virtual void visitParameterInfo(ParameterInfo *pi);
					virtual void visitVariableInfo(VariableInfo *vi);
					virtual void endVisitMethodCallInfo(MethodCallInfo *mi);

					virtual void startVisitObjectInfoGroup(ObjectInfoGroup *oi);
					virtual void startVisitObjectInfo(ObjectInfo *oi);
					virtual void visitFieldInfo(FieldInfo *fi);
					virtual void endVisitObjectInfo(ObjectInfo *oi);
					virtual void endVisitObjectInfoGroup(ObjectInfoGroup *oi);

					virtual ~DefaultGCVisitor();
			};

		}
	}
}

#endif
