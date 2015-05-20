#ifndef JCPP_LANG_INFO_JMETHODCALLVISITOR_H_
#define JCPP_LANG_INFO_JMETHODCALLVISITOR_H_

#include "jcpp/gc/visitor/IMethodCallVisitor.h"
#include "jcpp/lang/info/JThreadInfo.h"
#include "jcpp/lang/info/JMethodCallInfo.h"
#include "jcpp/util/JArrayList.h"

using namespace jcpp::gc::info;
using namespace jcpp::gc::visitor;
using namespace jcpp::gc;
using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp {
	namespace lang {
		namespace info {

			// @IgnoreReflection();
			// @IgnorePackageReflection();
			class JCPP_EXPORT JMethodCallVisitor: public IMethodCallVisitor{
			private:
				JList *result;
				JThreadInfo* currentThreadInfo;
				JMethodCallInfo* currentMethodCallInfo;

			public:
				JMethodCallVisitor();
				virtual void startVisitThreadInfo(ThreadInfo *ti);
				virtual void startVisitMethodCallInfo(MethodCallInfo *mi);
				virtual void visitParameterInfo(ParameterInfo *pi);
				virtual void visitVariableInfo(VariableInfo *vi);
				virtual void endVisitMethodCallInfo(MethodCallInfo *mi);
				virtual void endVisitThreadInfo(ThreadInfo *ti);

				JList* getResult();

				virtual ~JMethodCallVisitor();

			};
		}
	}
}

#endif
