#ifndef JCPP_GC_IGCVISITOR_H
#define JCPP_GC_IGCVISITOR_H

#include "jcpp/gc/visitor/IMethodCallVisitor.h"
#include "jcpp/gc/visitor/IObjectInfoGroupVisitor.h"
#include "jcpp/gc/visitor/IClassInfoVisitor.h"

namespace jcpp {
	namespace gc {
		namespace visitor {

			class IGCVisitor : public IObjectInfoGroupVisitor ,IClassInfoVisitor ,IMethodCallVisitor {
			public:
				virtual ~IGCVisitor() = 0;
			};

		}
	}
}

#endif
