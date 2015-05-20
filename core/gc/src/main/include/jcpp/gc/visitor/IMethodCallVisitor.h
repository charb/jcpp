#ifndef JCPP_GC_IMETHODCALLVISITOR_H
#define JCPP_GC_IMETHODCALLVISITOR_H

#include "jcpp/gc/info/MethodCallInfo.h"
#include "jcpp/gc/info/ParameterInfo.h"
#include "jcpp/gc/info/VariableInfo.h"
#include "jcpp/gc/ThreadInfo.h"

using namespace jcpp::gc::info;
using namespace jcpp::gc;

namespace jcpp {
	namespace gc {
		namespace visitor {

			class JCPP_EXPORT IMethodCallVisitor {
			public:
				virtual void startVisitMethodCallInfo(MethodCallInfo *mi) = 0;
				virtual void visitParameterInfo(ParameterInfo *pi) = 0;
				virtual void visitVariableInfo(VariableInfo *vi) = 0;
				virtual void endVisitMethodCallInfo(MethodCallInfo *mi) = 0;
				virtual void startVisitThreadInfo(ThreadInfo *ti) = 0;
				virtual void endVisitThreadInfo(ThreadInfo *ti) = 0;
				virtual ~IMethodCallVisitor() = 0;
			};

		}
	}
}

#endif
