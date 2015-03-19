#ifndef JCPP_GC_DefaULTMETHODCALLVISITOR_H
#define JCPP_GC_DefaULTMETHODCALLVISITOR_H

#include "jcpp/gc/visitor/IMethodCallVisitor.h"

using namespace jcpp::gc::info;

namespace jcpp {
	namespace gc {
		namespace visitor {

			class DefaultMethodCallVisitor : public IMethodCallVisitor {
			public:
				virtual void startVisitMethodCallInfo(MethodCallInfo *mi);
				virtual void visitParameterInfo(ParameterInfo *pi);
				virtual void visitVariableInfo(VariableInfo *vi);
				virtual void endVisitMethodCallInfo(MethodCallInfo *mi);
				virtual void startVisitThreadInfo(ThreadInfo *ti);
				virtual void endVisitThreadInfo(ThreadInfo *ti);
				virtual ~DefaultMethodCallVisitor();
			};

		}
	}
}

#endif
