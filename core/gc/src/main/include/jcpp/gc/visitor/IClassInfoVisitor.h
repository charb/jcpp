#ifndef JCPP_GC_ICLASSINFOVISITOR_H
#define JCPP_GC_ICLASSINFOVISITOR_H

#include "jcpp/gc/info/MethodCallInfo.h"
#include "jcpp/gc/info/ParameterInfo.h"
#include "jcpp/gc/info/VariableInfo.h"

using namespace jcpp::gc::info;

namespace jcpp {
	namespace gc {
		namespace visitor {

			class IClassInfoVisitor {
				public:
				virtual void startVisitClassInfo(ClassInfo *ci) = 0;
				virtual void visitStaticFieldInfo(FieldInfo *fi) = 0 ;
				virtual void endVisitClassInfo(ClassInfo *ci) = 0;
				virtual ~IClassInfoVisitor() = 0;
			};

		}
	}
}

#endif
